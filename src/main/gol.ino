int cells[6][12];

int isActive(int i, int j) {
  return cells[i][j];
}

  int getNumberOfActiveNeighbors(int i, int j) {
    int neighbors[8][2] = {
        {i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1},
        {i, j - 1}, {i, j + 1},
        {i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}
    };
    int numActiveCells = 0;
    for (int i = 0; i < 8; i++) {
      int k = (neighbors[i][0] + 12) % 12;
      int l = (neighbors[i][1] + 6) % 6;

      if (isActive(l, k) == 1) {
        numActiveCells += 1;
      }
    }
    return numActiveCells;
  }

void updateCells() {
  int cellCopy[6][12];
  for (int x = 0; x < 12; x++) {
    for (int y = 0; y < 6; y++) {
        int nActiveNeighbors = getNumberOfActiveNeighbors(x, y);
        if (!isActive(x, y) == 1 && nActiveNeighbors == 3) {
          cellCopy[y][x] = true;
        } else if (isActive(x, y) == 1 && (nActiveNeighbors == 2 || nActiveNeighbors == 3)) {
          cellCopy[y][x] = true;
        } else {
          cellCopy[y][x] = false;
        }
      }
    }
    for (int x = 0; x < 12; x++) {
      for (int y = 0; y < 6; y++) {
        cells[y][x] = cellCopy[y][x];
      }
    }
}

void fillRandom(int probability) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 12; j++) {
        int r = random(100);
        if (r <= probability) {
          cells[i][j] = 1;
        }
      }
    }
}

/*
 * Simple Game of Life animation
 */

void gameOfLifeAnimation() {
  fillRandom(20);
while(true) {
  setLed2DArraySingleColor(cells, 0, 1, 0, 0, 6, 12);
    shiftToShifter(2000);
    updateCells();
  }
}
