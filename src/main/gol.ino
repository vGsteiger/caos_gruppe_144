boolean cells[6][12];

int getNumberOfActiveNeighbors(int i, int j) {
  int neighbors[8][2] = {
        {i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1},
        {i, j - 1}, {i, j + 1},
        {i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}
    };
    int numActiveCells = 0;
    for (int m = 0; m < 8; m++) {
      //int k = (neighbors[m][0] + size) % size;
      //int l = (neighbors[m][1] + size) % size;

      //if (cells[k][l]) {
        //numActiveCells += 1;
      //}
    }
    return numActiveCells;
}
