/**
   Read sensory input, print it on the screen and then display temperature and humidity on the screen and then a corresponding effect
*/

int sunArray[6][12];
int rainDrops0[5][12];
int rainDrops1[5][12];

void tempSensorInfo() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  const char *cel = "C";
  const char *perc = "%";
  char bufferShort1[10];
  dtostrf(h, 5, 1, bufferShort1);
  strcat(bufferShort1, perc);
  if(checkIRSensor()){
        return;
  }
  printLetters(bufferShort1);
  char bufferShort2[10];
  dtostrf(t, 5, 1, bufferShort2);
  strcat(bufferShort2, cel);
  if(checkIRSensor()){
        return;
  }
  printLetters(bufferShort2);
  if (dht.readHumidity() > 100) {
    rainEffect(30000);
  } else if (dht.readTemperature() > 24) {
    sun(30000);
  } else {
    clouds(30000);
  }
}

void rainEffect(int seconds) {
  for (int s = 0; s < seconds; s++) {
    for (int x = 0; x < 12; x++) {
      setLedOn(x, 5, 1, 1, 1, 0);
      setLedOn(x, 5, 1, 1, 1, 1);
      int r = random(100);
      if (r < 35) {
        rainDrops0[4][x] = 1;
      }
      r = random(100);
      if (r < 35) {
        rainDrops1[4][x] = 1;
      }
    }
    rainDropFall(rainDrops0, rainDrops1);
  }
}

void rainDropFall(int rainDrops0[][12], int rainDrops1[][12]) {
  setLed2DArraySingleColor(rainDrops0, 0, 0, 0, 1, 5, 12);
  setLed2DArraySingleColor(rainDrops1, 1, 0, 0, 1, 5, 12);
  if(checkIRSensor()){
      return;
  }
  shiftToShifter(1000);
  int tempArray[5][12];
  for (int x = 0; x < 12; x++) {
    for (int y = 4; y >= 0; y--) {
      if (rainDrops0[y][x] == 1) {
        tempArray[y][x] == 0;
        if (y - 1 > 0) {
          tempArray[y - 1][x] == 1;
        }
      }
    }
  }
  memcpy(rainDrops0, tempArray, sizeof(tempArray));
  for (int x = 0; x < 12; x++) {
    for (int y = 4; y >= 0; y--) {
      if (rainDrops1[y][x] == 1) {
        tempArray[y][x] == 0;
        if (y - 1 > -1) {
          tempArray[y - 1][x] == 1;
        }
      }
    }
  }
  memcpy(rainDrops1, tempArray, sizeof(tempArray));
}

void sun(int seconds) {
  int sunArray[6][12];
  sunArray[1][9] = 1;
  sunArray[1][10] = 1;
  for (int i = 8; i < 12; i++) {
    for (int j = 2; j < 4; j++) {
      sunArray[j][i] = 1;
    }
  }
  sunArray[4][9] = 1;
  sunArray[4][10] = 1;
  for (int i = 0; i < seconds; i++) {
    setLed2DArraySingleColor(sunArray, 0, 1, 1, 0, 6, 12);
    setLed2DArraySingleColor(sunArray, 1, 1, 1, 0, 6, 12);
    if(checkIRSensor()){
        return;
    }
    shiftToShifter(1000);
    shiftSunToLeft(sunArray);
  }
}

void shiftSunToLeft(int sunArray[][12]) {
  int tempArray[6][12];
  for (int x = 0; x < 12; x++) {
    for (int y = 0; y < 6; y++) {
      if (x - 1 == -1) {
        x = 11;
      }
      tempArray[y][x - 1] = sunArray[y][x];
    }
  }
  memcpy(sunArray, tempArray, sizeof(tempArray));
}

void clouds(int seconds) {
  int cloudArray[6][12];
  for (int i = 0; i < 12; i++) {
    cloudArray[6][i] = 1;
  }
  int turn = 0;
  for (int i = 0; i < seconds; i++) {
    for (int i = 0; i < 12; i++) {
      cloudArray[5][i] = 0;
    }
    if (turn == 0) {
      for (int i = 1; i < 12; i = i + 2) {
        cloudArray[5][i] = 1;
      }
      turn = 1;
    } else {
      for (int i = 0; i < 12; i = i + 2) {
        cloudArray[5][i] = 1;
      }
      turn = 0;
    }
    setLed2DArraySingleColor(cloudArray, 0, 1, 1, 1, 6, 12);
    setLed2DArraySingleColor(cloudArray, 1, 1, 1, 1, 6, 12);
    if(checkIRSensor()){
        return;
    }
    shiftToShifter(1000);
  }
}
