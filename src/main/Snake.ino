
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
bool gameOver = false;

/*
   Method to initiate the snake game with all its parameters
*/
void init_snek() {
  s.snekLength = 3;
  int initDir = random(4);
  snekDir = initDir;
  int initPosX = random(3, 9);
  int initPosY = random(2, 4);
  s.snekBody[0][0] = initPosX;
  s.snekBody[0][1] = initPosY;
  for (int i = 1; i < s.snekLength; i++) {
    switch (snekDir) {
      case 0:
        d.x = 0;
        d.y = -1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY - 1;
        s.snekBody[i][1] = initPosY;
        break;
      case 1:
        d.x = -1;
        d.y = 0;
        initPosX = initPosX - 1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
        break;
      case 2:
        d.x = 0;
        d.y = 1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY + 1;
        s.snekBody[i][1] = initPosY;
        break;
      case 3:
        d.x = 1;
        d.y = 0;
        initPosX = initPosX + 1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
        break;
    }
  }
}

void init_game() {
  init_snek();
  f.x = random(12);
  f.y = random(6);
}

boolean render() {
  if (checkIRSensor()) {
    return false;
  }
  setLedOn(f.x, f.y, 0, 1, 0, 0);
  clearSnekArray();
  for (int i = 0; i < s.snekLength; i++) {
    snekArray[s.snekBody[i][1]][s.snekBody[i][0]] = 1;
  }
  setLed2DArraySingleColor(snekArray, 0, 1, 0, 0, 6, 12);
  shiftToShifter(3000);
  //Serial.println("Current snake array:");
  //for (int y = 0; y < 6; y++) {
  //  for (int x = 0; x < 12; x++) {
  //    if (f.x == x && f.y == y) {
  //      Serial.print("x");
  //    } else {
  //      Serial.print(snekArray[y][x]);
  //    }
  //  }
  //  Serial.println();
  //}
  //Serial.println();
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
    showGameOverMessage();
    return true;
  }

  bool grow = (head[0] == f.x && head[1] == f.y);
  if (grow) {
    s.snekLength++;
    f.x = random(12);
    f.y = random(6);
  }

  for (int i = s.snekLength - 2; i >= 0; i--) {
    s.snekBody[i + 1][0] = s.snekBody[i][0];
    s.snekBody[i + 1][1] = s.snekBody[i][1];
  }
  s.snekBody[0][0] += d.x;
  s.snekBody[0][1] += d.y;
  return false;
}

/*
   Loop over the whole snake game until lost!
*/
boolean snekGame() {
  if (!gameOver) {
    gameOver = advance();
    if(!render()){
      return false;
    }
  } else {
    Serial.println("Restarting after loosing!");
    restart();
  }
  return readControls();
}

/*
   Method to restart the game if a game has been lost
*/
void restart() {
  init_game();
  gameOver = false;
}

/*
   Method to read the current controls  (TO BE TESTED)
*/
boolean readControls() {
  Serial.println("Reading controls:");
  if (checkIRSensor()) {
    if (!changedEffect) {
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
    }
  }
  if (changedEffect) {
    changedEffect = false;
    return false;
  }
  return true;
}


/*
   Method to show a game Over message on the display when lost.
*/
void showGameOverMessage() {
  char gameOverMsg[10] = "Game over";
  if (!printLetters(gameOverMsg)) {
    return;
  }
}

/*
   Method to start the snake animation, calls setupSnake
*/
void startSnake() {
  Serial.println("Started snake!");
  Serial.println("Setting up snake!");
  init_game();
  if (!render()) {
    return;
  }  
  while (snekGame()) {
  }
  return;
}
