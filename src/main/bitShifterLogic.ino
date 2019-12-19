void shiftToShifter(int miliSeconds) 
  {
    miliSeconds = constrain (miliSeconds,    0, 101);
    int hertz = 55;
    int count;
    unsigned long delayProHertz = (miliSeconds/hertz)/2;
    Serial.println("Current delay");
    Serial.println(delayProHertz);
    for(int s = 0; s < miliSeconds; s++) {
      int currentShifter = currentAmountOfShifters-1;
      for(int hrtz = 0; hrtz < hertz; hrtz++) {
        changeLayer(0);
        digitalWrite(blank_pin, HIGH);//shut down the leds
        //Serial.println("Currently shifting out:");
        for(int i = currentAmountOfShifters-1; i >= 0; i--) {
          if(i == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if (i - 1 == currentShifter){
            SPI.transfer(anodes0[i]);
          } else if (i - 2 == currentShifter){
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
        
        changeLayer(1);
        digitalWrite(blank_pin, HIGH);//shut down the leds
        for(int i = currentAmountOfShifters-1; i >= 0; i--) {
          if(i == currentShifter) {
            SPI.transfer(anodes0[i]);
          } else if (i - 1 == currentShifter){
            SPI.transfer(anodes0[i]);
          } else if (i - 2 == currentShifter){
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
        currentShifter = currentShifter - 1;
      }
    }
    memset(anodes0, 0, sizeof(anodes0));
    memset(anodes1, 0, sizeof(anodes1));
    Serial.println(count);
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
