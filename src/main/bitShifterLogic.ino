/*
   Method to shift the current information in the anode arrays onto the shifters. Currently a single led lights up for (50/30)/2 times
*/
void shiftToShifter(int miliSeconds)
{
  for (int timeSpent = 0; timeSpent < miliSeconds / 100; timeSpent = timeSpent + 10) {
    int hertz = 30;
    int count;
    long delayProHertz = (50 / hertz);
    int currentShifter = currentAmountOfShifters - 1;
    for (int s = 0; s < 10; s++) {
      for (int hrtz = 0; hrtz < hertz; hrtz++) {

        digitalWrite(blank_pin, HIGH);//shut down the leds
        for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
          if (i == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if ((i - 1) % currentAmountOfShifters == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if ((i - 2) % currentAmountOfShifters == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else {
            SPI.transfer(0b00000000);
          }
        }

        // shift register to storage register
        digitalWrite(latch_pin, HIGH);
        digitalWrite(latch_pin, LOW);
        digitalWrite(blank_pin, LOW);  //enable pins

        digitalWrite(cathode_pin0, LOW);
        delay(delayProHertz);
        digitalWrite(cathode_pin0, HIGH);

        digitalWrite(blank_pin, HIGH);//shut down the leds
        for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
          if (i == currentShifter) {
            SPI.transfer(anodes1[i]);
          } else if ((i - 1) % currentAmountOfShifters == currentShifter) {
            SPI.transfer(anodes1[i]);
          } else if ((i - 2) % currentAmountOfShifters == currentShifter) {
            SPI.transfer(anodes1[i]);
          } else {
            SPI.transfer(0b00000000);
          }
        }

        // shift register to storage register
        digitalWrite(latch_pin, HIGH);
        digitalWrite(latch_pin, LOW);
        digitalWrite(blank_pin, LOW);  //enable pins

        digitalWrite(cathode_pin1, LOW);
        delay(delayProHertz);
        digitalWrite(cathode_pin1, HIGH);

        currentShifter = (currentShifter - 1) % currentAmountOfShifters; // If something doesn't work, it's because of this!
      }
    }
  }
  memset(anodes0, 0, sizeof(anodes0));
  memset(anodes1, 0, sizeof(anodes1));
}
