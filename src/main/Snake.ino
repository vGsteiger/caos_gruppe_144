
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
int timer = 0;

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
        initPosY = initPosY + 1;
        s.snekBody[i][1] = initPosY;
        break;
      case 1:
        d.x = -1;
        d.y = 0;
        initPosX = initPosX + 1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
        break;
      case 2:
        d.x = 0;
        d.y = 1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY - 1;
        s.snekBody[i][1] = initPosY;
        break;
      case 3:
        d.x = 1;
        d.y = 0;
        initPosX = initPosX - 1;
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
  clearSnekArray();
  for (int i = 0; i < s.snekLength; i++) {
    snekArray[s.snekBody[i][1]][s.snekBody[i][0]] = 1;
  }
  setLed2DArraySingleColor(snekArray, 0, 1, 0, 0, 6, 12);
  setLedOn(f.x, f.y, 0, 1, 0, 0);
  shiftToShifter(3000);
  return true;
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
  Serial.println("advancing one");
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
  if (s.snekBody[0][0] < 0 || s.snekBody[0][0] >= 12 || s.snekBody[0][1] < 0 || s.snekBody[0][1] >= 6) {
    showGameOverMessage();
    return true;
  }
  for (int i = 1; i < s.snekLength; i++) {
    if (s.snekBody[i][0] == s.snekBody[0][0] && s.snekBody[i][1] == s.snekBody[0][1]) {
      showGameOverMessage();
      return true;
    }
  }
  return false;
}

/*
   Loop over the whole snake game until lost!
*/
boolean snekGame() {
  if (!gameOver) {
    Serial.println("Not yet game over");
    gameOver = advance();
    if (!render()) {
      Serial.println("render returned false");
      return false;
    }
  } else {
    Serial.println("Restarting after loosing!");
    restart();
  }
  if (readControls()) {
    Serial.println("Controls gave true back");
    return true;
  } else {
    Serial.println("Controls gave false back");
    return false;
  }
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
  changedEffect = false;
  timer = 0;
  Serial.println("Started snake!");
  Serial.println("Setting up snake!");
  init_game();
  Serial.println("Snake set up");
  if (!render()) {
    Serial.println("render returned false");
    return;
  }
  while (snekGame()) {
    timer++;
    Serial.print("Run for x times: ");
    Serial.println(timer);
  }
  return;
}
