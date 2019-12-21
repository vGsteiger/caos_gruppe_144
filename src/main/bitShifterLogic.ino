/*
 * Method to shift the current information in the anode arrays onto the shifters. Currently a single led lights up for (50/30)/2 times 
 */
void shiftToShifter(int miliSeconds) 
  {
    long amountMilis = 0;
    for(int timeSpent = 0; timeSpent < miliSeconds/2; timeSpent = timeSpent + 50){    
    int hertz = 30;
    int count;
    long delayProHertz = (50/hertz)/2;
    int currentShifter = currentAmountOfShifters-1;
    for(int s = 0; s < 50; s++) {
      for(int hrtz = 0; hrtz < hertz; hrtz++) {
        changeLayer(0);
        digitalWrite(blank_pin, HIGH);//shut down the leds
        for(int i = currentAmountOfShifters-1; i >= 0; i--) {
          if(i == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if (i - 1 == currentShifter){
            SPI.transfer(anodes0[i]);
          }  else { 
            SPI.transfer(0b00000000);
          }
        }
       
        // shift register to storage register
        digitalWrite(latch_pin, HIGH);
        digitalWrite(latch_pin, LOW);
        digitalWrite(blank_pin, LOW);  //enable pins
        amountMilis = amountMilis + delayProHertz;
        delay(delayProHertz);
        
        changeLayer(1);
        digitalWrite(blank_pin, HIGH);//shut down the leds
        for(int i = currentAmountOfShifters-1; i >= 0; i--) {
          if(i == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if (i - 1 == currentShifter){
            SPI.transfer(anodes0[i]);
          } else { 
            SPI.transfer(0b00000000);
          }
          }
       
        // shift register to storage register
        digitalWrite(latch_pin, HIGH);
        digitalWrite(latch_pin, LOW);
        digitalWrite(blank_pin, LOW);  //enable pins
        delay(delayProHertz);
        amountMilis = amountMilis + delayProHertz;
        currentShifter = (currentShifter - 1) % currentAmountOfShifters; // If something doesn't work, it's because of this!
      }
    }
  }
    memset(anodes0, 0, sizeof(anodes0));
    memset(anodes1, 0, sizeof(anodes1));
    Serial.println(amountMilis);
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
