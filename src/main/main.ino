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

#include <SPI.h> // SPI Library used to clock data out to the shift registers
#include "DHT.h" // Humidity and Temperature sensor library
#include <IRremote.h>
#include <Time.h> // used to generate different random patterns and not always the same
#include <Wire.h>
#include <DS1307RTC.h> // Uses Pin 20/21
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
#define button 2 // Button to change mode, to be replaced by infrared!

int snekDir = 0;
boolean changedEffect = false;
int lastIRResult = 0;
int currentAmountOfShifters = 27;  // To be set depending on the current setup
byte anodes0[27]; // Array of Anodes for layer 0
byte anodes1[27]; // Array of Anodes for layer 1
int currentEffect = 0; // Integer value of the current effect in play
unsigned long lastSignal = 0; // long value for last effect (still here until replaced by infrared)
int currentAmountOfEffects = 1; // For the button, to be replaced
unsigned long timeStamp;
DHT dht(DHTPIN, DHTTYPE); // Humidity/Temperature variable


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
  pinMode(button, INPUT);

  attachInterrupt(digitalPinToInterrupt(button), blink, RISING);

  lastSignal = millis();

  digitalWrite(blank_pin, HIGH); //shut down the leds
  digitalWrite(latch_pin, LOW);  //shut down the leds

  irrecv.enableIRIn();
  irrecv.blink13(true);
  timeStamp = millis();
  welcomeAnimation();
}

void loop()
{
  delay(1);
  if (millis() - timeStamp > 10000) {  // sets the randomSeed depending on the current time to have a "true" random effect on every effect which random is used
    randomSeed(RTC.get());
  }
  checkIRSensor();
}

/**
  To handle the interrupt of the button input.
*/
void blink() {
  if (millis() - lastSignal > 200) {
    lastSignal = millis();
    currentEffect = (currentEffect + 1) % currentAmountOfEffects;
  }
}

void changeEffect(int result) {
  changedEffect = true;
  switch (result) {
    case 0x97483BFB: //Keypad button "0"
      Serial.println("Testeffect");
      test();
      break;
    case 0xE318261B: //Keypad button "1" -> not reacting quickly enough!
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
    case 0x20FE4DBB:
      Serial.println("Snake Game");
      setupSnake();
      break;
    case 0x8C22657B: // Keypad left
      changedEffect = false;
      snekDir = 1;
      break;
    case 0x449E79F:
      changedEffect = false;
      snekDir = 3;
      break;
    case 0x3D9AE3F7:
      changedEffect = false;
      snekDir = 2;
      break;
    case 0x1BC0157B:
      changedEffect = false;
      snekDir = 0;
      break;
    default:
      Serial.println("Default");
      break;
  }
}

// Keypad button 6: 20FE4DBB
// Keypad button 7: F076C13B
// Keypad button 8: A3C8EDDB
// Keypad button 9: E5CFBD7F
// Keypad button #: F0C41643
// Keypad button *: C101E57B
// Keypad button OK: 488F3CBB
// Keypad button left: 8C22657B
// Keypad button right: 449E79F
// Keypad button up: 3D9AE3F7
// Keypad button down: 1BC0157B


boolean checkIRSensor() {
  if (irrecv.decode(&results)) {
    if (millis() - lastSignal > 1000) {
      lastSignal = millis();
      lastIRResult = results.value;
      if (!(0xFFFFFFFF == results.value)) {
        changeEffect(results.value);
        Serial.println("Got a new signal!");
        Serial.println(results.value, HEX);
        irrecv.resume();
        return true;
      }
      irrecv.resume(); // Receive the next value
      return false;
    } else {
      irrecv.resume(); // Receive the next value
      return false;
    }
  } else {
    if (irrecv.decode(&results)) {
      irrecv.resume(); // Receive the next value
      return false;
    }
  }
}
