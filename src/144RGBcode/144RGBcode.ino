/*
 * 12x6x2 RGB LED Display
 * 
 * by Viktor Gsteiger, Moritz Würth, Joey Zgraggen
 * 
 * Latest release:
 * 26.11.2019
 * 
 * V0.1:
 * Basic set up and testing with the RGB Leds
 * 
 * V0.1.1:
 * Major revamp of setup and other functions to simplify the code and to make it work.
 * 
 * TODOs for V0.2:
 * Basic effects (wave, Letters)
 * First sensor implementation (temperature)
 * Button to change effect!
 * 
 * Future ideas: 
 * Unibas Logo, Clock implementation, Motion sensor
 * 
 */

#include <SPI.h>// SPI Library used to clock data out to the shift registers

// push the to storage register, Pin 12 at IC
#define latch_pin 49
// to shut enable/disable the register. Low enables, Pin 13 at IC
#define blank_pin 48
// used by SPI, must be pin 51 at Mega 2560, Pin 14 at IC
#define data_pin 51
// used by SPI, must be 52 at mega 2560, Pin 11 at IC
#define clock_pin 52

int currentAmountOfShifters = 2;  // To be set depending on the current setup
byte anodes[2]; // Array of Anodes

  void setup()
  {
   Serial.begin(115200); // Serial monitor for debugging 
   SPI.begin();
   SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz
   
   pinMode(latch_pin, OUTPUT);//Latch
   pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
   
   digitalWrite(blank_pin, HIGH); //shut down the leds
   digitalWrite(latch_pin, LOW);  //shut down the leds
  }
  
  void loop()
  {
    test();
  }

  void setLedOn(int x, int y, int red, int green, int blue, int layer)
  {
    x = constrain (x,    0, 15);      // x can only be between 0 and 15 as we have 16 leds length
    y = constrain (y, 0, 5);          // y can only be between 0 and 5 as we have 6 height
    red = constrain (red,    0, 1);   // Red can either be 1 or 0
    green = constrain (green,  0, 1); // Green can either be 1 or 0
    blue = constrain (blue,   0, 1);  // Blue can either be 1 or 0
    layer = constrain (layer,  0, 1);     // layer can only be 0 or 1 as we only have two layers
    
    int whichByte = int(((x+36*y)+1)/8);       // Calculate which byte be have to change
    int whichBit = ((y*36+x*3)+1)%8;

    Serial.println("Currently in byte:");
    Serial.println(whichByte);

    Serial.println("Currently in bit:");
    Serial.println(whichBit);

    if(whichBit == 0) {
      bitWrite(anodes[whichByte], 7, red);
      bitWrite(anodes[whichByte+1], 0, green);
      bitWrite(anodes[whichByte+1], 1, blue);
    } else if (whichBit == 7) {
      bitWrite(anodes[whichByte], whichBit-1, red);
      bitWrite(anodes[whichByte], whichBit, green);
      bitWrite(anodes[whichByte+1], 0, blue);
    } else {
      bitWrite(anodes[whichByte], whichBit-1, red);
      bitWrite(anodes[whichByte], whichBit, green);
      bitWrite(anodes[whichByte], whichBit+1, blue);
    }

    Serial.println("Currentl anode Array:");
    Serial.println(anodes[whichByte]);    
    
    shiftToShifter();
    memset(anodes, 0, sizeof(anodes));
  }

  void shiftToShifter() 
  {
    digitalWrite(blank_pin, HIGH);//shut down the leds
    for(int i = currentAmountOfShifters-1; i >= 0; i--) {
      Serial.println(anodes[i]);
      SPI.transfer(anodes[i]);
    }
   
    // shift register to storage register
    digitalWrite(latch_pin, HIGH);
    digitalWrite(latch_pin, LOW);
    digitalWrite(blank_pin, LOW);  //enable pins
    delay(250);
  }

  void test()
  {
    for(int i = 0; i < 3; i++) {
      setLedOn(i,0,1,0,0,0);
      setLedOn(i,0,0,1,0,0);
      setLedOn(i,0,0,0,1,0);
      setLedOn(i,0,1,1,0,0);
      setLedOn(i,0,1,0,1,0);
      setLedOn(i,0,0,1,1,0);
      setLedOn(i,0,1,1,1,0);
    }
  }
