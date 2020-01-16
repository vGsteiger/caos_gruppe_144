# Arduino Code for the 144 project

*Current version: v1.0*

Last major update: 15.01.2020

### Major hardware: 
* Arduino MEGA 2560 (from Banggood.com)
* RGB Led's
* 74hc595 Bitshifter
* DS1307RTC (Real time clock)
* IR Receiver
* DHT11 (Humidity/Temperature Sensor)
    
### Important pins: 
* Pin 7: Infrared receiver
* Pin 20: SDA of Clock
* Pin 21: SCL of Clock
* Pin 48: Blank pin of Bitshifters (13 at IC)
* Pin 49: Latch pin (12 at IC)
* Pin 51: Data pin (14 at IC)
* Pin 52: Clock pin (11 at IC)

### How to write your own effects:
    
Writing your own effects is easy and intuitive. You can either manually set all the LED's on in the effect by using setLedOn(int x, int y, int red, int green, int blue, int layer) (layer is not important in the current version) or use setLed2DArraySingleColor(int currArray[][12], int layer, int r, int g, int b, int maxH, int maxW) by giving it a 2D array with binary 1 or 0 where 1 means LED on and 0 LED off. 

After writing all your wanted LEDs onto the screen, you have to shift it out to actually be displayed. For this purpose use shiftToShifter(int miliSeconds) with your wanted amount of time in miliseconds.

You can also display letters on the screen. The method printLetters(char letters[]) takes a char array and displays it on the screen. All major letters are supported as well as numbers.

See test() as an easy example on how to use the mentioned functions.
