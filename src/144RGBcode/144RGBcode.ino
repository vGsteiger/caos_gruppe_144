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
 * Basic effects (wave, Letters) -> Implemented a rain function, 
 * First sensor implementation (temperature)
 * Button to change effect! -> Done!
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
#define clock_pin0 52

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

  void setup()
  {
   Serial.begin(115200); // Serial monitor for debugging 
   SPI.begin();
   SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz
   
   pinMode(latch_pin, OUTPUT);//Latch
   pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
   pinMode(cathode_pin0, OUTPUT);
   pinMode(cathode_pin1, OUTPUT);
   pinMode(button, INPUT);
   attachInterrupt(digitalPinToInterrupt(button), blink, RISING);
   lastSignal = millis();
   
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

  void setLedOn(int x, int y, int red, int green, int blue, int layer)
  {
    x = constrain (x,    0, 15);      // x can only be between 0 and 15 as we have 16 leds length
    y = constrain (y, 0, 5);          // y can only be between 0 and 5 as we have 6 height
    red = constrain (red,    0, 1);   // Red can either be 1 or 0
    green = constrain (green,  0, 1); // Green can either be 1 or 0
    blue = constrain (blue,   0, 1);  // Blue can either be 1 or 0
    layer = constrain (layer,  0, 1);     // layer can only be 0 or 1 as we only have two layers
    
    int whichByte = int(((x*3+36*y)+1)/8);       // Calculate which byte be have to change
    int whichBit = ((y*36+x*3)+1)%8;          //  Calculate which bit in that byte we have to set on

    //Serial.println("Currently in byte:");
    //Serial.println(whichByte);

    //Serial.println("Currently in bit:");
    //Serial.println(whichBit);
    /**
     * Choses between the two available layers of our LED RGB Cubic.
     */
    switch(layer) {
      case 0:
        if(whichBit == 0) {
          bitWrite(anodes0[whichByte], 7, red);
          bitWrite(anodes0[whichByte+1], 0, green);
          bitWrite(anodes0[whichByte+1], 1, blue);
        } else if (whichBit == 7) {
          bitWrite(anodes0[whichByte], whichBit-1, red);
          bitWrite(anodes0[whichByte], whichBit, green);
          bitWrite(anodes0[whichByte+1], 0, blue);
        } else {
          bitWrite(anodes0[whichByte], whichBit-1, red);
          bitWrite(anodes0[whichByte], whichBit, green);
          bitWrite(anodes0[whichByte], whichBit+1, blue);
        }
      case 1:
        if(whichBit == 0) {
          bitWrite(anodes1[whichByte], 7, red);
          bitWrite(anodes1[whichByte+1], 0, green);
          bitWrite(anodes1[whichByte+1], 1, blue);
        } else if (whichBit == 7) {
          bitWrite(anodes1[whichByte], whichBit-1, red);
          bitWrite(anodes1[whichByte], whichBit, green);
          bitWrite(anodes1[whichByte+1], 0, blue);
        } else {
          bitWrite(anodes1[whichByte], whichBit-1, red);
          bitWrite(anodes1[whichByte], whichBit, green);
          bitWrite(anodes1[whichByte], whichBit+1, blue);
        }
    }   
    
  }

  void shiftToShifter(int miliSeconds) 
  {
    int hertz = 120;
    int delayProHertz = (int)(miliSeconds/hertz)/2;
    for(int s = 0; s < miliSeconds; s++) {
    for(int hrtz = 0; hrtz < hertz; hrtz++) {
    changeLayer(0);
    digitalWrite(blank_pin, HIGH);//shut down the leds
    for(int i = currentAmountOfShifters-1; i >= 0; i--) {
      SPI.transfer(anodes0[i]);
    }
   
    // shift register to storage register
    digitalWrite(latch_pin, HIGH);
    digitalWrite(latch_pin, LOW);
    digitalWrite(blank_pin, LOW);  //enable pins
    delay(delayProHertz);
    
    changeLayer(1);
    digitalWrite(blank_pin, HIGH);//shut down the leds
    for(int i = currentAmountOfShifters-1; i >= 0; i--) {
      SPI.transfer(anodes1[i]);
    }
   
    // shift register to storage register
    digitalWrite(latch_pin, HIGH);
    digitalWrite(latch_pin, LOW);
    digitalWrite(blank_pin, LOW);  //enable pins
    delay(delayProHertz);
    }
    }
    memset(anodes0, 0, sizeof(anodes0));
    memset(anodes1, 0, sizeof(anodes1));
  }

  /**
   * Switch between the layers (we use 2 layers in this project). TODO: Porperly implement this!
   */
  void changeLayer(int layer) {
    if(layer == 0) {
      digitalWrite(cathode_pin0, HIGH);
      digitalWrite(cathode_pin1, LOW);
    } else {
      digitalWrite(cathode_pin1, HIGH);
      digitalWrite(cathode_pin0, LOW);
    }
  }

  /*
   * Effects:
   */

  void test()
  {
    //for(int i = 0; i < 5; i++) {
      setLedOn(3,0,1,0,0,0);
      shiftToShifter(100);
      setLedOn(3,0,0,1,0,0);
      shiftToShifter(100);
      setLedOn(3,0,0,0,1,0);
      shiftToShifter(100);
    //}
  }

  /**
   * rainEffect if the humidity sensor perceives a specific value.
   * TODO: Implement sensor logic. -> I would rather do that in another method
   */
  void rainEffect(int seconds) {
    int rainDrops0[5][12];
    int rainDrops1[5][12];
    for(int s = 0; s < seconds; s++){
      for (int x=0;x<12;x++) {
        setLedOn(x,5,1,1,1,0);
        setLedOn(x,5,1,1,1,1);
        rainDrops0[4][x] = random(2);
        rainDrops1[4][x] = random(2);
      }
      rainDropFall(rainDrops0, rainDrops1);
    }
  }

  void rainDropFall(int rainDrops0[][12],int rainDrops1[][12]) {
    setLed2DArraySingleColor(rainDrops0,0,0,0,1,5,12);
    setLed2DArraySingleColor(rainDrops1,0,0,0,1,5,12);
    int tempArray[5][12];
    for(int x=0;x<12;x++) {
      for(int y=4;y>=0;y--) {
        if(rainDrops0[y][x] == 1) {
          tempArray[y][x] == 0;
          if(y-1>0) {
            tempArray[y-1][x] == 1;
          }
        }
      }
    }
    rainDrops0 = tempArray;
    for(int x=0;x<12;x++) {
      for(int y=4;y>=0;y--) {
        if(rainDrops1[y][x] == 1) {
          tempArray[y][x] == 0;
          if(y-1>-1) {
            tempArray[y-1][x] == 1;
          }
        }
      }
    }
    memcpy(rainDrops1, tempArray, sizeof(tempArray));
  }

  void shiftGlobalArrayLeft() {
    int tempArray[6][12];
    for(int x=0;x<12;x++) {
      for(int y=0;y<6;y++) {
        if(dispArray[y][x] == 1) {
          if(x-1>-1) {
            tempArray[y][x-1] = 1;
          }
        }
      }
    }
    memcpy(dispArray, tempArray, sizeof(tempArray));
  }

  /**
   * Sets the the 2d Array given to a specific height to a single color.
   * Combinations of r, g ,b.
   */
  void setLed2DArraySingleColor(int currArray[][12], int layer, int r, int g, int b, int maxH, int maxW) {
    for(int x=0;x<maxW;x++) {
      for(int y=0;y<maxH;y++) {
        if(currArray[y][x] == 1) {
          setLedOn(x,y,r,g,b,layer);
        }
      }
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
