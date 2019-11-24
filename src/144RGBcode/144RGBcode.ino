/*
 * 12x6x2 RGB LED Display
 * 
 * by Viktor Gsteiger, Moritz Würth, Joey Zgraggen
 * 
 * Latest release:
 * 24.11.2019
 * 
 * V0.1:
 * Basic set up and testing with the RGB Leds
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

/*
 * Pin definition:
 * Pins correspont to a Arduino Mega 2560 ordered on Banggood.com
 */
#include <SPI.h>
#define latch_pin 44  // To be tested
#define blank_pin 45  // To be tested (probably needs 1k ohm resistor)
#define data_pin 51   // To be tested
#define clock_pin 52  // To be tested
#define cathode_pin 1 // To select either layer of our setup for the bit angle modulation

/*
 * Important variables
 */
byte leds0[27], leds1[27];  // Storing the display information with the current colors and which leds are set on

int layer=0;                // keeps track of our current cathode layer
int BAM_Bit, BAM_Counter=0; // Bit Angle Modulation variables to keep track of the clock 

/*
 * SETUP BEGIN:
 */

  void setup() {
    SPI.setBitOrder(MSBFIRST);            //Most Significant Bit First
    SPI.setDataMode(SPI_MODE0);           // Mode 0 Rising edge of data, keep clock low
    SPI.setClockDivider(SPI_CLOCK_DIV2);  //Run the data at 16MHz/2 - 8MHz
    noInterrupts();                       // kill interrupts for the most important setups
  
    Serial.begin(115200); // Serial monitor for debugging 
    TCCR1A = B00000000;   // Register A all 0's since we're not toggling any pins
    TCCR1B = B00001011;   // bit 3 set to place in CTC mode, will call an interrupt on a counter match
    TIMSK1 = B00000010;   // bit 1 set to call the interrupt on an OCR1A match
    OCR1A=30;             // To be tested
    
    pinMode(latch_pin, OUTPUT); // Latch pin
    pinMode(data_pin, OUTPUT);  // MOSI DATA pin
    pinMode(clock_pin, OUTPUT); // SPI Clock pin
    //BlankMode(blank_pin, OUTPUT); // Output Enable
    SPI.begin();                // Start the SPI library
    interrupts();               // Enable interrupts
    
  }

/*
 * SETUP END
 */

/*
 * LOOP BEGIN:
 */

  void loop() {
    // TODO: Interrupts with the button and sensory data. Also more functions!
    test();
  }

/*
 * LOOP END
 */

/*
 * LED BEGIN:
 */

  void LED(int l, int x, int y, int red, int green, int blue){
    
    l = constrain (l,  0, 1);         // layer can only be 0 or 1 as we only have two layers
    x = constrain (x,    0, 15);      // x can only be between 0 and 15 as we have 16 leds length
    y = constrain (y, 0, 5);          // y can only be between 0 and 5 as we have 6 height
    red = constrain (red,    0, 1);   // Red can either be 1 or 0
    green = constrain (green,  0, 1); // Green can either be 1 or 0
    blue = constrain (blue,   0, 1);  // Blue can either be 1 or 0
      
    int whichbyte = int((x+36*y)/8);  // Calculate which byte be have to chang
    int wholebyte = (x+36*y);           // Calculate exactly which LED we want to address (color comes later, this number will always be on the BLANK pin)
    Serial.print(whichbyte);

    switch(l) { // Decide on which layer we will have to operate on
      case 0:   // Operate on layer 0 
        bitWrite(leds0[whichbyte], (256-(wholebyte-(8*whichbyte))), red);     // Set the red bit of our current byte to either 0 or 1
        bitWrite(leds0[whichbyte], (256-(wholebyte-(8*whichbyte)+1)), green); // Set the green bit of our current byte to either 0 or 1
        bitWrite(leds0[whichbyte], (256-(wholebyte-(8*whichbyte)+2)), blue);  // Set the blue bit of our current byte to either 0 or 1
      case 1:   // Operate on layer 1
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte), red);     // Set the red bit of our current byte to either 0 or 1
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+1, green); // Set the green bit of our current byte to either 0 or 1
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+2, blue);  // Set the blue bit of our current byte to either 0 or 1
    }
    
  }

/*
 * LED END
 */

/*
 * ISR START:
 */

  ISR(TIMER1_COMPA_vect){

  int shift_out; // Iterative variable used in this method
  
  PORTL |= 1<<4;  // Turn all LEDS off

  // Each layer has the chance to light up twice per 4 bit angle modulation
  if(BAM_Counter==8) {
    BAM_Bit++;
  } else {
    if(BAM_Counter==24) {
      BAM_Bit++;
    } else {
      if(BAM_Counter==56) {
        BAM_Bit++;
      }
    }
  }
  
  BAM_Counter++;
  
  switch (BAM_Bit){ // Depending on the BAM bit we will now light up either layer 0 or 1. We change layer with the 
  case 0:           // method changeLayer()
   changeLayer(0);
   for(shift_out=0; shift_out<27; shift_out++) {
    SPI.transfer(leds0[shift_out]);
   }
   break;
  case 1:
   changeLayer(1);
   for(shift_out=0; shift_out<27; shift_out++) {
    SPI.transfer(leds1[shift_out]);
   }
   break;
  case 2:
   changeLayer(0);
   for(shift_out=0; shift_out<27; shift_out++) {
    SPI.transfer(leds0[shift_out]);
   }
   break;
  case 3:
   changeLayer(1);
   for(shift_out=0; shift_out<27; shift_out++) {
    SPI.transfer(leds1[shift_out]);
   }
   // If we have reached the end of one bit angle modulation counter we reset he counter and the BAM_bit:
   if(BAM_Counter==120){
    BAM_Counter=0;
    BAM_Bit=0;
   }
   break;
  }
    
  PORTL |= 1<<5;    //Latch pin HIGH
  PORTL &= ~(1<<5); //Latch pin LOW
  PORTL &= ~(1<<4); //Blank pin LOW to turn on the LEDs with the new data

  pinMode(blank_pin, OUTPUT);//moved down here so outputs are all off until the first call of this function
  }

/*
 * ISR END
 */

  void changeLayer(int l){
    l = constrain (l,  0, 1); // Layer can only be 1 or 0
    if(l == 0) {
      digitalWrite(cathode_pin,LOW);  // Change the cathode layer with the cathope_pin to 0
    } else {
      digitalWrite(cathode_pin,HIGH); // Change the cathode layer with the cathope_pin to 1
    }
  }

/*
 * ANIMATIONS START:
 */

  void test(){  // Test function for debugging:
    //for (int i=0;i<12;i++){
    //  for (int j=0;i<6;i++){
        delay(1000);
        LED (0,2,0, 0, 0, 1);
      //}
    //}
  }
