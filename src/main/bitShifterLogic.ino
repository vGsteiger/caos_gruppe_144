void shiftToShifter(int miliSeconds)
{
  int hertz = 120;
  int delayProHertz = (int)(miliSeconds / hertz) / 2;
  for (int s = 0; s < miliSeconds; s++) {
    for (int hrtz = 0; hrtz < hertz; hrtz++) {
      changeLayer(0);
      digitalWrite(blank_pin, HIGH);//shut down the leds
      for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
        SPI.transfer(anodes0[i]);
      }

      // shift register to storage register
      digitalWrite(latch_pin, HIGH);
      digitalWrite(latch_pin, LOW);
      digitalWrite(blank_pin, LOW);  //enable pins
      delay(delayProHertz);

      changeLayer(1);
      digitalWrite(blank_pin, HIGH);//shut down the leds
      for (int i = currentAmountOfShifters - 1; i >= 0; i--) {
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
   Switch between the layers (we use 2 layers in this project). TODO: Porperly implement this!
*/
void changeLayer(int layer) {
  if (layer == 0) {
    digitalWrite(cathode_pin0, HIGH);
    digitalWrite(cathode_pin1, LOW);
  } else {
    digitalWrite(cathode_pin1, HIGH);
    digitalWrite(cathode_pin0, LOW);
  }
}
