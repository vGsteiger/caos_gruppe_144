/*
   Print a char array onto the screen. Method handles the String and loads the letters one by one onto the screen by calling the methods for the letters. The methods then
   load the letters manually into the letterBuffer and a letter then gets shifted out until the last letter is reached.
*/

int tempArray[6][4];
int largeTempArray[6][12];
int dispArray[6][12]; // Array containing all LEDs in one color
int letterBuffer[6][4]; // Letterbuffer for the Letters next to be loaded

boolean printLetters(char letters[]) {
  clearDispArray();
  letters = strlwr(letters);
  for (int i = 0; i < strlen(letters); i++) {
    clearLetterBuffer();
    int m = 0;
    //Serial.println(letters[i]);
    switch (letters[i]) {
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
        loadT();
        break;
      case 'u':
        loadU();
        break;
      case 'v':
        loadV();
        break;
      case 'w':
        loadW();
        break;
      case 'x':
        loadX();
        break;
      case 'y':
        loadY();
        break;
      case 'z':
        loadZ();
        break;
      case '%':
        loadPercentage();
        break;
      case '.':
        loadPoint();
        break;
      case ' ':
        break;
      case '0':
        load0();
        break;
      case '1':
        load1();
        break;
      case '2':
        load2();
        break;
      case '3':
        load3();
        break;
      case '4':
        load4();
        break;
      case '5':
        load5();
        break;
      case '6':
        load6();
        break;
      case '7':
        load7();
        break;
      case '8':
        load8();
        break;
      case '9':
        load9();
        break;
      case '/':
        loadSlash();
        break;
      case ':':
        loadDoublepoint();
        break;
      default:
        break;
    }
    if (i == strlen(letters)) {
      m = 50;
    } else {
      m = 5;
    }
    for (int s = 0; s < m; s++) {
      setLed2DArraySingleColor(dispArray, 0, 1, 1, 1, 6, 12);
      shiftGlobalArrayLeft();

      if (checkIRSensor()) {
        return false;
      }
      shiftToShifter(600);
    }
  }
  return true;
}

void shiftGlobalArrayLeft() {
  clearLargeTempArray();
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 12; x++) {
      if (x - 1 > -1) {
        largeTempArray[y][x - 1] = dispArray[y][x];
      } else {
        largeTempArray[y][11] = letterBuffer[y][0];
      }
    }
  }
  shiftLetterBufferLeft();
  clearDispArray();
  for (int yy = 0; yy < 6; yy++) {
    for (int xx = 0; xx < 12; xx++) {
      dispArray[yy][xx] = largeTempArray[yy][xx];
    }
  }
}

void shiftLetterBufferLeft() {
  clearTempArray();
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 4; x++) {
      if ((x - 1) > -1) {
        tempArray[y][x - 1] = letterBuffer[y][x];
      } else {
        tempArray[y][3] = 0;
      }
    }
  }
  clearLetterBuffer();
  for (int yy = 0; yy < 6; yy++) {
    for (int xx = 0; xx < 4; xx++) {
      letterBuffer[yy][xx] = tempArray[yy][xx];
    }
  }
}

void clearLetterBuffer() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 4; p++) {
      letterBuffer[l][p] = 0;
    }
  }
}

void clearTempArray() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 4; p++) {
      tempArray[l][p] = 0;
    }
  }
}

void clearLargeTempArray() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 12; p++) {
      largeTempArray[l][p] = 0;
    }
  }
}

void clearDispArray() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 12; p++) {
      dispArray[l][p] = 0;
    }
  }
}

void loadA() {
  for (int l = 0; l < 5; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[2][1] = 1;
  letterBuffer[5][1] = 1;
}

void loadB() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
  }
  letterBuffer[0][1] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[4][2] = 1;
}

void loadC() {
  for (int l = 1; l < 5; l++) {
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
  for (int l = 0; l < 6; l++) {
    if (l == 0 || l == 5) {
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
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
  }
  letterBuffer[0][1] = 1;
  letterBuffer[3][2] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[0][2] = 1;
  letterBuffer[5][2] = 1;
}

void loadF() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
  }
  letterBuffer[3][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[5][2] = 1;
}

void loadG() {
  for (int l = 0; l < 6; l++) {
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
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
}

void loadI() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][1] = 1;
  }
}

void loadJ() {
  for (int l = 1; l < 6; l++) {
    letterBuffer[l][2] = 1;
  }
  letterBuffer[0][1] = 1;
  letterBuffer[1][0] = 1;
}

void loadK() {
  for (int l = 0; l < 6; l++) {
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
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
  }
  letterBuffer[0][1] = 1;
  letterBuffer[0][2] = 1;
}

void loadM() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[4][1] = 1;
  letterBuffer[3][1] = 1;
}

void loadN() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[4][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[2][1] = 1;
}

void loadO() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[5][1] = 1;
  letterBuffer[0][1] = 1;
}

void loadP() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
  }
  letterBuffer[5][1] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][2] = 1;
  letterBuffer[4][2] = 1;
}

void loadQ() {
  for (int l = 1; l < 5; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[5][1] = 1;
  letterBuffer[0][1] = 1;
  letterBuffer[0][2] = 1;

}

void loadR() {
  for (int l = 0; l < 6; l++) {
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

void loadT() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][1] = 1;
  }
  letterBuffer[5][0] = 1;
  letterBuffer[5][2] = 1;
}

void loadU() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[0][1] = 1;
}

void loadV() {
  for (int l = 1; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[0][1] = 1;
}

void loadW() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[1][1] = 1;
}

void loadX() {
  for (int l = 0; l < 6; l++) {
    if (l != 2 && l != 3) {
      letterBuffer[l][0] = 1;
      letterBuffer[l][2] = 1;
    }
  }
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
}

void loadY() {
  for (int l = 0; l < 4; l++) {
    letterBuffer[l][1] = 1;
  }
  letterBuffer[4][0] = 1;
  letterBuffer[5][0] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][2] = 1;
}

void loadZ() {
  for (int l = 0; l < 3; l++) {
    letterBuffer[0][l] = 1;
    letterBuffer[5][l] = 1;
  }
  letterBuffer[4][2] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[1][0] = 1;
}

void loadPercentage() {
  letterBuffer[5][0] = 1;
  letterBuffer[0][2] = 1;
  letterBuffer[0][0] = 1;
  letterBuffer[1][0] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][2] = 1;
}

void loadPoint() {
  letterBuffer[0][1] = 1;
}

void load0() {
  for (int l = 1; l < 5; l++) {
    letterBuffer[l][0] = 1;
    letterBuffer[l][2] = 1;
  }
  letterBuffer[5][1] = 1;
  letterBuffer[0][1] = 1;
}

void load1() {
  for (int l = 0; l < 6; l++) {
    letterBuffer[l][2] = 1;
  }
  letterBuffer[4][1] = 1;
}

void load2() {
  letterBuffer[0][0] = 1;
  letterBuffer[0][1] = 1;
  letterBuffer[0][2] = 1;
  letterBuffer[1][0] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][2] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[4][0] = 1;
  letterBuffer[5][1] = 1;
}

void load3() {
  letterBuffer[0][0] = 1;
  letterBuffer[0][1] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[5][0] = 1;
}

void load4() {
  letterBuffer[0][2] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[2][0] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[2][2] = 1;
  letterBuffer[3][0] = 1;
  letterBuffer[3][2] = 1;
  letterBuffer[4][0] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][0] = 1;
  letterBuffer[5][2] = 1;
}

void load5() {
  letterBuffer[0][0] = 1;
  letterBuffer[0][1] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[2][2] = 1;
  letterBuffer[3][0] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[4][0] = 1;
  letterBuffer[5][0] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[5][2] = 1;
}

void load6() {
  letterBuffer[0][1] = 1;
  letterBuffer[1][2] = 1;
  letterBuffer[1][0] = 1;
  letterBuffer[2][0] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][0] = 1;
  letterBuffer[4][0] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[5][2] = 1;
}
void load7() {
  letterBuffer[0][0] = 1;
  letterBuffer[1][0] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][0] = 1;
  letterBuffer[5][1] = 1;
  letterBuffer[5][2] = 1;
}
void load8() {
  for (int l = 0; l < 6; l++) {
    if (l != 3) {
      letterBuffer[l][0] = 1;
      letterBuffer[l][2] = 1;
    }
  }
  letterBuffer[0][1] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[5][1] = 1;
}
void load9() {
  letterBuffer[3][1] = 1;
  letterBuffer[4][0] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[5][1] = 1;
  for (int l = 1; l < 5; l++) {
    letterBuffer[l][2] = 1;
  }
  letterBuffer[0][0] = 1;
  letterBuffer[0][1] = 1;
}

void loadSlash() {
  letterBuffer[5][2] = 1;
  letterBuffer[4][2] = 1;
  letterBuffer[3][1] = 1;
  letterBuffer[2][1] = 1;
  letterBuffer[1][0] = 1;
  letterBuffer[0][0] = 1;
}

void loadDoublepoint() {
  letterBuffer[2][1] = 1;
  letterBuffer[4][1] = 1;
}
