void setLedOn(int x, int y, int red, int green, int blue, int layer)
{
  x = constrain (x,    0, 11);      // x can only be between 0 and 11 as we have 12 leds length
  y = constrain (y, 0, 5);          // y can only be between 0 and 5 as we have 6 height
  red = constrain (red,    0, 1);   // Red can either be 1 or 0
  green = constrain (green,  0, 1); // Green can either be 1 or 0
  blue = constrain (blue,   0, 1);  // Blue can either be 1 or 0
  layer = constrain (layer,  0, 1);     // layer can only be 0 or 1 as we only have two layers

  int whichByte = int(((x * 3 + 36 * y) + 1) / 8); // Calculate which byte be have to change
  int whichBit = ((y * 36 + x * 3) + 1) % 8; //  Calculate which bit in that byte we have to set on

  //Serial.println("Currently in byte:");
  //Serial.println(whichByte);

  //Serial.println("Currently in bit:");
  //Serial.println(whichBit);
  /**
     Choses between the two available layers of our LED RGB Cubic.
  */
  switch (layer) {
    case 0:
      if (whichBit == 0) {
        bitWrite(anodes0[whichByte], 7, red);
        bitWrite(anodes0[whichByte + 1], 0, green);
        bitWrite(anodes0[whichByte + 1], 1, blue);
      } else if (whichBit == 7) {
        bitWrite(anodes0[whichByte], whichBit - 1, red);
        bitWrite(anodes0[whichByte], whichBit, green);
        bitWrite(anodes0[whichByte + 1], 0, blue);
      } else {
        bitWrite(anodes0[whichByte], whichBit - 1, red);
        bitWrite(anodes0[whichByte], whichBit, green);
        bitWrite(anodes0[whichByte], whichBit + 1, blue);
      }
    case 1:
      if (whichBit == 0) {
        bitWrite(anodes1[whichByte], 7, red);
        bitWrite(anodes1[whichByte + 1], 0, green);
        bitWrite(anodes1[whichByte + 1], 1, blue);
      } else if (whichBit == 7) {
        bitWrite(anodes1[whichByte], whichBit - 1, red);
        bitWrite(anodes1[whichByte], whichBit, green);
        bitWrite(anodes1[whichByte + 1], 0, blue);
      } else {
        bitWrite(anodes1[whichByte], whichBit - 1, red);
        bitWrite(anodes1[whichByte], whichBit, green);
        bitWrite(anodes1[whichByte], whichBit + 1, blue);
      }
  }

}
