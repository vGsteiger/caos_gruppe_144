/*
 * 12x6x2 RGB LED Display
 * 
 * by Viktor Gsteiger, Moritz Würth, Joey Zgraggen
 * 
 * Latest release:
 * 07.12.2019
 * 
 * V0.1:
 * Basic set up and testing with the RGB Leds
 * 
 * V0.1.1:
 * Major revamp of setup and other functions to simplify the code and to make it work.
 * 
 * TODOs for V0.2:
 * Basic effects (wave, Letters) -> Implemented a rain function, and first letters
 * First sensor implementation (temperature) -> Done!
 * Button to change effect! -> Done!
 * 
 * Future ideas: 
 * Unibas Logo, Clock implementation, Motion sensor
 * 
 */

#include <SPI.h>// SPI Library used to clock data out to the shift registers
#include "DHT.h"

// push the to storage register, Pin 12 at IC
#define latch_pin 49
// to shut enable/disable the register. Low enables, Pin 13 at IC
#define blank_pin 48
// used by SPI, must be pin 51 at Mega 2560, Pin 14 at IC
#define data_pin 51
// used by SPI, must be 52 at mega 2560, Pin 11 at IC
#define clock_pin0 52
#define DHTPIN 2
#define DHTTYPE DHT11
// Cathode Pin, can be any pin
#define cathode_pin0 3
#define cathode_pin1 4
// Button to change mode:
#define button 2

int currentAmountOfShifters = 2;  // To be set depending on the current setup
byte anodes0[27]; // Array of Anodes for layer 0
byte anodes1[27]; // Array of Anodes for layer 1
int currentEffect = 0;
unsigned long lastSignal = 0;
int currentAmountOfEffects = 1;
int dispArray[6][12];
int letterBuffer[6][3];
int lettersToBeDisp;
DHT dht(DHTPIN, DHTTYPE);

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
   lettersToBeDisp = 0;
   
   digitalWrite(blank_pin, HIGH); //shut down the leds
   digitalWrite(latch_pin, LOW);  //shut down the leds
  }
  
  void loop()
  {
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
