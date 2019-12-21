/*
 * 12x6x2 RGB LED Display
 * 
 * by Viktor Gsteiger, Moritz Würth, Joey Zgraggen
 * 
 * Latest release:
 * 21.12.2019
 * 
 * Current effects: 
 * Clock (not tested), Firework (not Tested), Game of Life (not tested), Stars (not tested), Temperature effects (not tested)
 * 
 * V0.1:
 * Basic set up and testing with the RGB Leds
 * 
 * V0.1.1:
 * Major revamp of setup and other functions to simplify the code and to make it work.
 * 
 * V0.2:
 * Game of Life, new Multiplexing algorithm, alphabet, firework, stars, temperature Effects
 * 
 * TODO V0.3:
 * Clock
 * Infrared control
 * 
 * 
 * Future ideas: 
 * Unibas Logo, Clock implementation, Motion sensor
 * 
 */
#include "RTClib.h" // Real time clock library
#include <SPI.h> // SPI Library used to clock data out to the shift registers
#include "DHT.h" // Humidity and Temperature sensor library

#define latch_pin 49 // push the to storage register, Pin 12 at IC
#define blank_pin 48 // to shut enable/disable the register. Low enables, Pin 13 at IC
#define data_pin 51 // used by SPI, must be pin 51 at Mega 2560, Pin 14 at IC
#define clock_pin0 52 // used by SPI, must be 52 at mega 2560, Pin 11 at IC
#define DHTPIN 2 // Humidity/temperature sensor pin
#define DHTTYPE DHT11 // Humidity/temperature sensor model
#define cathode_pin0 3 // Cathode Pin, to be tested!
#define cathode_pin1 4 // Same as above!
#define button 2 // Button to change mode, to be replaced by infrared!

int currentAmountOfShifters = 1;  // To be set depending on the current setup
byte anodes0[27]; // Array of Anodes for layer 0
byte anodes1[27]; // Array of Anodes for layer 1
int currentEffect = 0; // Integer value of the current effect in play
unsigned long lastSignal = 0; // long value for last effect (still here until replaced by infrared) 
int currentAmountOfEffects = 1; // For the button, to be replaced
int dispArray[6][12]; // Array containing all LEDs in one color
int letterBuffer[6][4]; // Letterbuffer for the Letters next to be loaded
DHT dht(DHTPIN, DHTTYPE); // Humidity/Temperature variable
RTC_DS1307 rtc; // Real time clock variable

  void setup()
  {
   Serial.begin(115200); // Serial monitor for debugging 
   SPI.begin(); // Begin the SPI library 
   SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz
   dht.begin();
   
   pinMode(latch_pin, OUTPUT);//Latch
   pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
   pinMode(cathode_pin0, OUTPUT);// To be tested whether it works or has to be replaced
   pinMode(cathode_pin1, OUTPUT);
   pinMode(button, INPUT); // To be replaced by infrared
   attachInterrupt(digitalPinToInterrupt(button), blink, RISING); // For button, to be replaced
   lastSignal = millis(); // Initial last signal
   
   digitalWrite(blank_pin, HIGH); //shut down the leds
   digitalWrite(latch_pin, LOW);  //shut down the leds

   if (! rtc.begin()) { // Start real time clock
    Serial.println("Couldn't find RTC");
    while (1);
   }
   if (! rtc.isrunning()) { // adjust the clock time to now
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }
  
  void loop()
  {
    // To be replaced with infrared logic
    switch(currentEffect) {
      case 0:
        test();
    }
 }

    /**
   * To handle the interrupt of the button input.
   */
  void blink() {
    if(millis()-lastSignal > 200){
      lastSignal = millis();
      currentEffect = (currentEffect + 1) % currentAmountOfEffects;
    }
  }
