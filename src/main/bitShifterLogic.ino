/*
   Method to shift the current information in the anode arrays onto the shifters. Currently a single led lights up for (50/30)/2 times
*/
void shiftToShifter(int miliSeconds)
{
  long a = 100L;
  long b = 54L;
  long delayProHertz = (a / b);
  miliSeconds = constrain (miliSeconds,    100, 100000);
  for (int timeSpent = 0; timeSpent < miliSeconds; timeSpent = timeSpent + 100) {
    int currentShifter = currentAmountOfShifters - 1;
    for (int hrtz = 0; hrtz < currentAmountOfShifters; hrtz++) {
      digitalWrite(blank_pin, HIGH);//shut down the leds
      for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
        if (i == currentShifter) {
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
      digitalWrite(cathode_pin1, LOW);
      delay(delayProHertz);
      digitalWrite(cathode_pin0, HIGH);
      digitalWrite(cathode_pin1, HIGH);

      //digitalWrite(blank_pin, HIGH);//shut down the leds
      //for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
      //  if (i == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else if ((i + 1) % currentAmountOfShifters == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else if ((i + 2) % currentAmountOfShifters == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else if ((i + 3) % currentAmountOfShifters == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else if ((i + 4) % currentAmountOfShifters == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else if ((i + 5) % currentAmountOfShifters == currentShifter) {
      //    SPI.transfer(anodes1[i]);
      //  } else {
      //    SPI.transfer(0b00000000);
      //  }
      //}

      // shift register to storage register
      //digitalWrite(latch_pin, HIGH);
      //digitalWrite(latch_pin, LOW);
      //digitalWrite(blank_pin, LOW);  //enable pins

      //digitalWrite(cathode_pin1, LOW);
      //delay(delayProHertz);
      //digitalWrite(cathode_pin1, HIGH);

      currentShifter--;
    }
  }
  memset(anodes0, 0, sizeof(anodes0));
  memset(anodes1, 0, sizeof(anodes1));
}
