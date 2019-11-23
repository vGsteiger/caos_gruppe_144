/*
 * 12x6x2 RGB LED Display
 * 
 * by Viktor Gsteiger, Moritz Würth, Joey Zgraggen
 * 
 * Latest release:
 * 20.11.2019
 * 
 * V1:
 * Basic set up and testing with the RGB Leds
 */

/*
 * Basic setup:
 */
#include <SPI.h>
#define latch_pin 44// can be any pin
#define blank_pin 45// can be any pin, just use 1k ohm
#define data_pin 51// used by SPI, must be pin 11
#define clock_pin 52// used by SPI, must be 13

#define cathode_pin 1

/*
 * Common variables to the code:
 */
 int shift_out;//used in the code a lot in for(i= type loops

// Storing the brightness of our leds:
// 4 bit resolution with 72 leds per layer
byte leds0[27], leds1[27];


int layer=0; // keeps track of our cathode layer
int BAM_Bit, BAM_Counter=0; // Bit Angle Modulation variables to keep track of things

//These variables can be used for other things
unsigned long start;//for a millis timer to cycle through the animations
int globalRed, globalGreen, globalBlue;

  void setup() {
    SPI.setBitOrder(MSBFIRST);//Most Significant Bit First
    SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
    SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz
    noInterrupts();// kill interrupts until everybody is set up
  
    Serial.begin(115200);// if you need it?
    TCCR1A = B00000000;//Register A all 0's since we're not toggling any pins
    TCCR1B = B00001011;//bit 3 set to place in CTC mode, will call an interrupt on a counter match
    TIMSK1 = B00000010;//bit 1 set to call the interrupt on an OCR1A match
    OCR1A=35; // you can play with this, but I set it to 30, which means:
    
    //finally set up the Outputs
    pinMode(latch_pin, OUTPUT);//Latch
    pinMode(data_pin, OUTPUT);//MOSI DATA
    pinMode(clock_pin, OUTPUT);//SPI Clock
    //pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
    SPI.begin();//start up the SPI library
    interrupts();//let the show begin, this lets the multiplexing start
    
  }

  void loop() {
    // put your main code here, to run repeatedly:
    test();
  }

  void LED(int l, int x, int y, int red, byte green, byte blue){
    
    l = constrain (l,  0, 1);
    x = constrain (x,    0, 15);
    y = constrain (y, 0, 6);
    red = constrain (red,    0, 1);
    green = constrain (green,  0, 1);
    blue = constrain (blue,   0, 1);
      
    int whichbyte = int(((y*36)+(x*3)+1)/8);
    int wholebyte = (y*36)+(x*3)+1;
    switch(l) {
      case 0: 
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte), red);
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+1, green);
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+2, blue);
        Serial.println(leds0[0]);
      case 1:
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte), red);
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+1, green);
        bitWrite(leds0[whichbyte], wholebyte-(8*whichbyte)+2, blue);
        Serial.println(leds1[0]);    
    }
    
  }

  // LED END

  // ISR START

  ISR(TIMER1_COMPA_vect){
  
  PORTL |= 1<<4;
  
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
  
  switch (BAM_Bit){
  case 0:
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
   if(BAM_Counter==120){
    BAM_Counter=0;
    BAM_Bit=0;
   }
   break;
  }
    
  PORTL |= 1<<5;//Latch pin HIGH
  PORTL &= ~(1<<5);//Latch pin LOW
  PORTL &= ~(1<<4);//Blank pin LOW to turn on the LEDs with the new data
  
  layer++;//inrement the anode level
  
  if(layer==1) {
    layer=0;
  }
  
  pinMode(blank_pin, OUTPUT);//moved down here so outputs are all off until the first call of this function
  }

  // ISR END

  void changeLayer(int l){
    l = constrain (l,  0, 1);
    if(l == 0) {
      digitalWrite(cathode_pin,LOW);
    } else {
      digitalWrite(cathode_pin,HIGH);
    }
  }

  void test(){
    //for (int i=0;i<12;i++){
    //  for (int j=0;i<6;i++){
        LED (0,0,0, 1, 0, 0);
        delay(100);
        LED (0,0,0, 0, 1, 0);
        delay(100);
        LED (0,0,0, 0, 0, 1);
        delay(100);
      //}
    //}
  }
