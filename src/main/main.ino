/*
   12x6x2 RGB LED Display

   by Viktor Gsteiger, Moritz Würth, Joey Zgraggen

   Latest release:
   21.12.2019

   Current effects:
   Clock (not tested), Firework (not Tested), Game of Life (not tested), Stars (not tested), Temperature effects (not tested)

   V0.1:
   Basic set up and testing with the RGB Leds

   V0.1.1:
   Major revamp of setup and other functions to simplify the code and to make it work.

   V0.2:
   Game of Life, new Multiplexing algorithm, alphabet, firework, stars, temperature Effects

   V0.3:
   Revamp of changelayer and other minor bug fixes all over the code

   TODO V1.0:
   Fix the not working parts of the code: 
   - Alphabet (Viktor)
   - clock (Viktor)
   - Firework (Moritz)
   - GOL/better random seeding (Joey)
   - Stars (Moritz)
   - Temperature Effects (Viktor)
   - IR Control and Snake (Viktor)

*/
#include "RTClib.h" // Real time clock library
#include <SPI.h> // SPI Library used to clock data out to the shift registers
#include "DHT.h" // Humidity and Temperature sensor library
#include <IRremote.h>
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define latch_pin 49 // push the to storage register, Pin 12 at IC -> green
#define blank_pin 48 // to shut enable/disable the register. Low enables, Pin 13 at IC -> violett
#define data_pin 51 // used by SPI, must be pin 51 at Mega 2560, Pin 14 at IC -> brown
#define clock_pin0 52 // used by SPI, must be 52 at mega 2560, Pin 11 at IC -> blue
#define DHTPIN 2 // Humidity/temperature sensor pin
#define DHTTYPE DHT11 // Humidity/temperature sensor model
#define cathode_pin0 24 // Cathode Pin, to be tested!
#define cathode_pin1 26 // Same as above!

int currentAmountOfShifters = 27;  // To be set depending on the current setup
byte anodes0[27]; // Array of Anodes for layer 0
byte anodes1[27]; // Array of Anodes for layer 1
int currentEffect = 0; // Integer value of the current effect in play
unsigned long lastSignal = 0; // long value for last measured time
int dispArray[6][12]; // Array containing all LEDs in one color
int letterBuffer[6][4]; // Letterbuffer for the Letters next to be loaded
DHT dht(DHTPIN, DHTTYPE); // Humidity/Temperature variable
RTC_DS1307 rtc; // Real time clock variable

void setup()
{
  Serial.begin(115200); // Serial monitor for debugging
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz
  dht.begin();

  pinMode(latch_pin, OUTPUT);//Latch
  pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
  pinMode(cathode_pin0, OUTPUT);
  pinMode(cathode_pin1, OUTPUT);

  lastSignal = millis();

  digitalWrite(blank_pin, HIGH); //shut down the leds
  digitalWrite(latch_pin, LOW);  //shut down the leds
  
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop()
{
  delay(1);
}

void changeEffect(int result) {
    switch (result) {
      case 0x97483BFB: //Keypad button "0"
        Serial.println("Testeffect");
        test();
        break;
      case 0xE318261B: //Keypad button "1"
        Serial.println("Firework");
        firework();
        break;
      case 0x511DBB: //Keypad button "2"
        Serial.println("GOL");
        gameOfLifeAnimation();
        break;
      case 0xEE886D7F:  //Keypad button "3"
        Serial.println("Clock");
        clockAnimation();
        break;
      case 0x52A3D41F: //Keypad button "4"
        Serial.println("Stars");
        starAnimation();
        break;
      case 0xD7E84B1B: //Keypad button "5"
        Serial.println("Temperature effects");
        tempSensorInfo();
        break;
      default:
        Serial.println("Default");
        break;
    }
  }

  boolean checkIRSensor(){
    if (millis() - lastSignal > 200) {
      lastSignal = millis();
      if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        changeEffect(results.value);
        irrecv.resume(); // Receive the next value
        return true;
      }
    } else {
      if (irrecv.decode(&results)){
        //changeEffect(results.value);
        irrecv.resume(); // Receive the next value
        return false;
      }
      }
  }
