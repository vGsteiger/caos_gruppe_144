
typedef struct food {
  int x;
  int y;
} food;

typedef struct snek {
  int snekLength;
  int snekBody[72][2];
} snek;

typedef struct dir {
  int x;
  int y;
} dir;

struct food f;
struct dir d;
struct snek s;
int snekArray[6][12];
int tempSnekArray[6][12];
bool gameOver = false;

void init_snek() {
  s.snekLength = 3;
  int initDir = random(4);
  snekDir = initDir;
  int initPosX = random(12);
  int initPosY = random(6);
  s.snekBody[0][0] = initPosX;
  s.snekBody[0][0] = initPosY;
  for (int i = 1; i < s.snekLength; i++) {
    switch (initDir) {
      case 0:
        d.x = 0;
        d.y = -1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY - 1;
        s.snekBody[i][1] = initPosY;
      case 1:
        d.x = -1;
        d.y = 0;
        initPosX = initPosX - 1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
      case 2:
        d.x = 0;
        d.y = 1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY + 1;
        s.snekBody[i][1] = initPosY;
      case 3:
        d.x = 1;
        d.y = 0;
        initPosX = initPosX + 1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
    }
  }
}

void init_game() {
  init_snek();
  f.x = random(12);
  f.y = random(6);
}

void render() {
  clearSnekTempArray();
  for (int i = 0; i < s.snekLength; i++) {
    tempSnekArray[s.snekBody[i][1]][s.snekBody[i][0]];
  }
  setLedOn(f.x, f.y, 0, 1, 0, 0);
  clearSnekArray();
  for (int yy = 0; yy < 6; yy++) {
    for (int xx = 0; xx < 4; xx++) {
      snekArray[yy][xx] = tempSnekArray[yy][xx];
    }
  }
  setLed2DArraySingleColor(snekArray, 0, 1, 0, 0, 6, 12);
  shiftToShifter(10000);
  for(int y = 0; y < 6; y++) {
  for(int x = 0; x < 12; x++) {
    Serial.println(snekArray[y][x]);
  }
  }
}

void clearSnekTempArray() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 12; p++) {
      tempSnekArray[l][p] = 0;
    }
  }
}

void clearSnekArray() {
  for (int l = 0; l < 6; l++) {
    for (int p = 0; p < 12; p++) {
      snekArray[l][p] = 0;
    }
  }
}

/**
   moves the snake forward
   returns true if the game is over
*/
bool advance() {
  int head[2] = {s.snekBody[0][0], s.snekBody[0][1]};
  if (head[0] < 0 || head[0] >= 12 || head[1] < 0 || head[1] >= 6) {
    delay(1000);
    showGameOverMessage();
    return true;
  }
  for (int i = 1; i < s.snekLength; i++) {
    if (s.snekBody[i][0] == head[0] && s.snekBody[i][1] == head[1]) {
      delay(1000);
      showGameOverMessage();
      return true;
    }
  }

  bool grow = (head[0] == f.x && head[1] == f.y);
  if (grow) {
    s.snekLength++;
    f.x = random(12);
    f.y = random(6);
  }

  for (int i = s.snekLength - 1; i >= 0; i--) {
    s.snekBody[i + 1][0] = s.snekBody[i][0];
    s.snekBody[i + 1][1] = s.snekBody[i][1];
  }
  s.snekBody[0][0] += d.x;
  s.snekBody[0][1] += d.y;
  return false;
}

void setupSnake() {
  init_game();
  render();
  while (true) {
    snekGame();
  }
}

void snekGame() {
  if (!gameOver) {
    render();
    gameOver = advance();
  } else {
    restart();
  }
  if (readControls()) {} else {
    return;
  }
}

void restart() {
  init_game();
  gameOver = false;
}

boolean readControls() {
  if (checkIRSensor()) {
      switch (snekDir) {
        case 0:
          d.x = 0;
          d.y = -1;
          break;
        case 1:
          d.x = -1;
          d.y = 0;
          break;
        case 2:
          d.x = 0;
          d.y = 1;
          break;
        case 3:
          d.x = 1;
          d.y = 0;
          break;
      }
      return true;
    } else {
      if(changedEffect) {
        changedEffect = false;
        return false;
      }
    }
  }

void showGameOverMessage() {
  char gameOverMsg[10] = "Game over";
  if (checkIRSensor()) {
    return;
  }
  if (!printLetters(gameOverMsg)) {
    return;
  }
}

void startSnake() {
  setupSnake();
}
