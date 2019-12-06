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
        int r = random(100);
        if(r < 35) {
          rainDrops0[4][x] = 1;
        }
        r = random(100);
        else {
          rainDrops1[4][x] = 1;
        }
      }
      rainDropFall(rainDrops0, rainDrops1);
    }
  }

  

  void rainDropFall(int rainDrops0[][12],int rainDrops1[][12]) {
    setLed2DArraySingleColor(rainDrops0,0,0,0,1,5,12);
    setLed2DArraySingleColor(rainDrops1,0,0,0,1,5,12);
    shiftToShifter(1000);
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
    memcpy(rainDrops0, tempArray, sizeof(tempArray));
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

  void sun(int seconds) {
    //TODO
  }

  // TODO: shiftLetterBufferLeft, loadLetters, letters
