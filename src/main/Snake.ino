/**
 * Snake
 * Implementation of the classical Snake game 
 * where the snake moved constantly and the player
 * have to avoid intersections with itself and borders.
 * When the snake eats food it grows and speeds up a little bit.
 * 
 * 23 Jun 2016
 * by Sergey Royz and hunter Buzzell
 */
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

void init_snek() {
  s.snekLength = 3;
  int initDir = random(4);
  snekDir = initDir;
  int initPosX = random(12);
  int initPosY = random(6);
  s.snekBody[0][0] = initPosX;
  s.snekBody[0][0] = initPosX;
  for (int i = 1; i < s.snekLength; i++) {
    switch(initDir) {
      case 0:
        d.x = 0;
        d.y = -1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY-1;
        s.snekBody[i][1] = initPosY;
      case 1:
        d.x = -1;
        d.y = 0;
        initPosX = initPosX-1;
        s.snekBody[i][0] = initPosX;
        s.snekBody[i][1] = initPosY;
      case 2:
        d.x = 0;
        d.y = 1;
        s.snekBody[i][0] = initPosX;
        initPosY = initPosY+1;
        s.snekBody[i][1] = initPosY;
      case 3:
        d.x = 1;
        d.y = 0;
        initPosX = initPosX+1;
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
  int tempArray[6][12];
  for (int i = 0; i < s.snekLength; i++) {
    tempArray[s.snekBody[i][1]][s.snekBody[i][0]];
  }
  setLedOn(f.x, f.y, 0, 1, 0, 0);
  memcpy(snekArray, tempArray, sizeof(tempArray));
  setLed2DArraySingleColor(snekArray, 0, 1, 0, 0, 6, 12);
  shiftToShifter(1000);
}

/**
 * moves the snake forward
 * returns true if the game is over
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
  snekGame();
}

void snekGame() {
  if (!gameOver) {
    render();
    gameOver = advance();
  } else {
    restart();
  }
  if(readControls()){} else {
    return;
  }
}

void restart() {  
  init_game();
  gameOver = false;
}

boolean readControls() {
  if(checkIRSensor()){
    // TODO: Check whether correct last result
    if(results.value == 0) {
    switch(snekDir) {
      case 0:
        d.x = 0;
        d.y = -1;
      case 1:
        d.x = -1;
        d.y = 0;
      case 2:
        d.x = 0;
        d.y = 1;
      case 3:
        d.x = 1;
        d.y = 0;      
    }
    return true;
  } else {
    return false;
  }
  }
}

void showGameOverMessage() {
  char gameOverMsg[10] = "Game over";
  if(checkIRSensor()){
        return;
  }
  printLetters(gameOverMsg);
  if(checkIRSensor()){
        return;
  }
}
