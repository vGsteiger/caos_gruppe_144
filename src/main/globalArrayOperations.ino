/**
  Sets the the 2d Array given to a specific height to a single color.
  Combinations of r, g ,b.
*/
void setLed2DArraySingleColor(int currArray[][12], int layer, int r, int g, int b, int maxH, int maxW) {
  for (int x = 0; x < maxW; x++) {
    for (int y = 0; y < maxH; y++) {
      if (currArray[y][x] == 1) {
        setLedOn(x, y, r, g, b, layer);
      }
    }
  }
}
