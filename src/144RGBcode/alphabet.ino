    void printLetters(String letters) {
      lettersToBeDisp = letters.length();
      letters.toLowerCase();
      for(int i = 0; i < letters.length(); i++) {
        int m = 0;
        switch(letters.charAt(i)) {
          case 'a':
            loadA();
            break;
          case 'b':
            loadB();
            break;
          case 'c':
            loadC();
            break;
          case 'd':
            loadD();
            break;
          case 'e':
            loadE();
            break;
          case 'f':
            loadF();
            break;
          case 'g':
            loadG();
            break;
          case 'h':
            loadH();
            break;
          case 'i':
            loadI();
            break;
          case 'j':
            loadJ();
            break;
          case 'k':
            loadK();
            break;
          case 'l':
            loadL();
            break;
          case 'm':
            loadM();
            break;
          case 'n':
            loadN();
            break;
          case 'o':
            loadO();
            break;
          case 'p':
            loadP();
            break;
          case 'q':
            loadQ();
            break;
          case 'r':
            loadR();
            break;
          case 's':
            loadS();
            break;
          case 't':
            break;
          case 'u':
            break;
          case 'v':
            break;
          case 'w':
            break;
          case 'x':
            break;
          case 'y':
            break;
          case 'z':
            break;
          case '%':
            break;
          case '0':
            break;
          case '1':
            break;
          case '2':
            break;
          case '3':
            break;
          case '4':
            break;
          case '5':
            break;
          case '6':
            break;
          case '7':
            break;
          case '8':
            break;
          case '9':
            break;
          default:
            break;
            }
            if(i == letters.length() -1) {
              m = 12;
            } else {
              m = 3;
            }
          for(int s = 0; s < m; s++){
            shiftGlobalArrayLeft();
            setLed2DArraySingleColor(dispArray,0,1,1,0,6,12);
            shiftToShifter(1000);
          }
          lettersToBeDisp--;
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
          shiftLetterBufferLeft();
        } else if(dispArray[y][x] == 1) {
          if(x-1>-1) {
            tempArray[y][x-1] = 1;
          }
        }
      }
    }
    memcpy(dispArray, tempArray, sizeof(tempArray));
  }

  void shiftLetterBufferLeft() {
    int tempArray[6][3];
    for(int x = 0; x < 3; x++) {
      for(int y = 0; y < 6; y++) {
        if(x-1 == -1) {
          continue;
        } else {
          tempArray[y][x-1] = letterBuffer[y][x];
      }
      }
    }
    memcpy(letterBuffer, tempArray, sizeof(tempArray));
  }

  void loadA() {
    for(int l = 0; l < 5; l++) {
      letterBuffer[l][0] = 1;
      letterBuffer[l][2] = 1;
    }
    letterBuffer[2][1] = 1;
    letterBuffer[5][1] = 1;
  }

  void loadB() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[2][1] = 1;
    letterBuffer[3][1] = 1;
    letterBuffer[5][1] = 1;
    letterBuffer[1][2] = 1;
    letterBuffer[4][1] = 1;
  }

  void loadC() {
    for(int l = 1; l < 5; l++) {
      letterBuffer[l][0] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[1][1] = 1;
    letterBuffer[4][1] = 1;
    letterBuffer[5][1] = 1;
    letterBuffer[0][2] = 1;
    letterBuffer[5][2] = 1;
  }

  void loadD() {
    for(int l = 0; l < 6; l++) {
      if(l == 0 || l == 5) {
        letterBuffer[l][0] = 1;
      } else {
        letterBuffer[l][0] = 1;
        letterBuffer[l][2] = 1;
      }
    }
    letterBuffer[0][1] = 1;
    letterBuffer[5][1] = 1;
  }

  void loadE() {
    for(int l = 0; l < 6; l++) {
        letterBuffer[l][0] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[2][1] = 1;
    letterBuffer[3][1] = 1;
    letterBuffer[5][1] = 1;
    letterBuffer[0][2] = 1;
    letterBuffer[5][2] = 1;
  }

  void loadF() {
        for(int l = 0; l < 6; l++) {
        letterBuffer[l][0] = 1;
    }
    letterBuffer[2][1] = 1;
    letterBuffer[3][1] = 1;
    letterBuffer[5][1] = 1;
    letterBuffer[5][2] = 1;
  }

  void loadG() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[5][1] = 1;
    letterBuffer[0][2] = 1;
    letterBuffer[1][2] = 1;
    letterBuffer[2][2] = 1;
    letterBuffer[5][2] = 1;
  }

  void loadH() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
      letterBuffer[l][2] = 1;
    }
    letterBuffer[2][1] = 1;
    letterBuffer[3][1] = 1;
  }

  void loadI() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][1] = 1;
    }
  }

  void loadJ() {
    for(int l = 1; l < 6; l++) {
      letterBuffer[l][2] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[1][0] = 1;
  }

  void loadK() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
    }
    letterBuffer[2][1] = 1;
    letterBuffer[3][1] = 1;
    letterBuffer[0][2] = 1;
    letterBuffer[1][2] = 1;
    letterBuffer[4][2] = 1;
    letterBuffer[5][2] = 1;
  }

  void loadL() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
    }
    letterBuffer[0][1] = 1;
    letterBuffer[0][2] = 1;
  }

  void loadM() {
    for(int l = 0; l < 6; l++) {
      letterBuffer[l][0] = 1;
      letterBuffer[l][2] = 1;
    }
    letterBuffer[4][1] = 1;
    letterBuffer[3][1] = 1;  
    }

    void loadN() {
      for(int l = 0; l < 6; l++) {
        letterBuffer[l][0] = 1;
        letterBuffer[l][2] = 1;
      }
      letterBuffer[4][1] = 1;
      letterBuffer[3][1] = 1; 
      letterBuffer[2][1] = 1; 
    }

    void loadO() {
      for(int l = 1; l < 5; l++) {
        letterBuffer[l][0] = 1;
        letterBuffer[l][2] = 1;
      }
      letterBuffer[5][1] = 1;
      letterBuffer[0][1] = 1; 
      }

  void loadP() {
      for(int l = 0; l < 6; l++) {
        letterBuffer[l][0] = 1;
      }
      letterBuffer[5][1] = 1;
      letterBuffer[2][1] = 1; 
      letterBuffer[3][2] = 1; 
      letterBuffer[4][2] = 1; 
  }

  void loadQ() {
          for(int l = 1; l < 5; l++) {
        letterBuffer[l][0] = 1;
        letterBuffer[l][2] = 1;
      }
      letterBuffer[5][1] = 1;
      letterBuffer[0][1] = 1; 
      letterBuffer[0][2] = 1; 

  }

  void loadR() {
          for(int l = 0; l < 6; l++) {
        letterBuffer[l][0] = 1;
      }
      letterBuffer[5][1] = 1;
      letterBuffer[2][1] = 1; 
      letterBuffer[3][2] = 1; 
      letterBuffer[4][2] = 1; 
      letterBuffer[1][1] = 1; 
      letterBuffer[0][2] = 1; 
  }

  void loadS() {
      letterBuffer[0][0] = 1;
      letterBuffer[0][1] = 1; 
      letterBuffer[1][2] = 1; 
      letterBuffer[2][0] = 1; 
      letterBuffer[2][1] = 1; 
      letterBuffer[2][2] = 1; 
      letterBuffer[3][0] = 1; 
      letterBuffer[3][1] = 1; 
      letterBuffer[3][2] = 1; 
      letterBuffer[4][0] = 1; 
      letterBuffer[5][1] = 1; 
      letterBuffer[5][2] = 1; 
  }
