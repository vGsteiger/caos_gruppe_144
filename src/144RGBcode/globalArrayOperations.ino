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

    void shiftGlobalArrayLeft() {
    int nextLetter = 0;
    for(int i = 0; i < 6; i++) {
      if(dispArray[i][11] == 1) {
        nextLetter = -1;
      }
    }
    if(nextLetter != -1 && lettersToBeDisp > 0) {
      nextLetter = 1;
    }
    int tempArray[6][12];
    for(int x=0;x<12;x++) {
      for(int y=0;y<6;y++) {
        if(x == 11 && nextLetter == 1) {
          tempArray[y][11] = letterBuffer[y][0];
          //shiftLetterBufferLeft();
        } else if(dispArray[y][x] == 1) {
          if(x-1>-1) {
            tempArray[y][x-1] = 1;
          }
        }
      }
    }
    memcpy(dispArray, tempArray, sizeof(tempArray));
  }
