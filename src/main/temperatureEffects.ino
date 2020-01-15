/**
   Read sensory input, print it on the screen and then display temperature and humidity on the screen and then a corresponding effect
*/

int sunArray[6][12];
int rainDrops[5][12];
int rainTempArray[5][12];

void tempSensorInfo() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  const char *cel = "C    ";
  const char *perc = "%    ";
  char bufferShort1[18];
  dtostrf(h, 5, 1, bufferShort1);
  strcat(bufferShort1, perc);
  if (checkIRSensor()) {
    return;
  }
  //if (!printLetters(bufferShort1)) {
  //  return;
  //}
  char bufferShort2[18];
  dtostrf(t, 5, 1, bufferShort2);
  strcat(bufferShort2, cel);
  if (checkIRSensor()) {
    return;
  }
  //if (!printLetters(bufferShort2)) {
  //  return;
  //}
  if (dht.readHumidity() > 60) {
    rainEffect(1000);
  } else if (dht.readTemperature() > 24) {
    sun(1000);
  } else {
    clouds(1000);
  }
}

void rainEffect(int seconds) {
  for (int s = 0; s < seconds; s++) {
    for (int x = 0; x < 12; x++) {
      setLedOn(x, 5, 1, 1, 1, 0);
      int r = random(100);
      if (r < 20) {
        rainDrops[4][x] = 1;
      }
    }
    rainDropFall();
  }
}

void rainDropFall() {
  setLed2DArraySingleColor(rainDrops, 0, 0, 0, 1, 5, 12);
  if (checkIRSensor()) {
    return;
  }
  shiftToShifter(1000);
  clearRainTmpArray();
  for (int y = 4; y >= 0; y--) {
    for (int x = 0; x < 12; x++) {
      if (rainDrops[y][x] == 1) {
        if (y - 1 >= 0) {
          Serial.println("Writing into array");
          rainTempArray[y - 1][x] = 1;
        }
      }
    }
  }
  clearRainArray();
  for (int yy = 0; yy < 6; yy++) {
    for (int xx = 0; xx < 12; xx++) {
      rainDrops[yy][xx] = rainTempArray[yy][xx];
    }
  }
}

void clearRainArray() {
  for (int l = 0; l < 5; l++) {
    for (int p = 0; p < 12; p++) {
      rainDrops[l][p] = 0;
    }
  }
}

void clearRainTmpArray() {
  for (int l = 0; l < 5; l++) {
    for (int p = 0; p < 12; p++) {
      rainTempArray[l][p] = 0;
    }
  }
}

void sun(int seconds) {
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
    if (checkIRSensor()) {
      for (int l = 0; l < 5; l++) {
        for (int p = 0; p < 12; p++) {
          sunArray[l][p] = 0;
        }
      }
      return;
    }
    shiftToShifter(1000);
    shiftSunToLeft();
  }
}

void shiftSunToLeft() {
  int sunTempArray[6][12];
  for (int l = 0; l < 5; l++) {
    for (int p = 0; p < 12; p++) {
      sunTempArray[l][p] = 0;
    }
  }
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 12; x++) {
      if (sunArray[y][x] == 1) {
        if (x - 1 < 0) {
          x = 11;
        }
        sunTempArray[y][x - 1] = 1;
      }
    }
  }
  for (int l = 0; l < 5; l++) {
    for (int p = 0; p < 12; p++) {
      sunArray[l][p] = 0;
    }
  }
  for (int yy = 0; yy < 6; yy++) {
    for (int xx = 0; xx < 12; xx++) {
      sunArray[yy][xx] = sunTempArray[yy][xx];
    }
  }
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 12; x++) {
      Serial.print(sunArray[y][x]);
    }
    Serial.println();
  }
  Serial.println();
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
    if (checkIRSensor()) {
      return;
    }
    shiftToShifter(1000);
  }
}
