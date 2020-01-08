
void test()
{
  //if(checkIRSensor()){
    //  return;
  //}
  Serial.println("Test runs!");
  for(int c = 0; c < 3; c++) {
  for(int j = 0; j < 6; j++) {
    for(int i = 0; i < 12; i++) {
      //setLedOn(i, j, 1, 0, 0, 0);
      //shiftToShifter(1000);
      //setLedOn(i, j, 0, 1, 0, 0);
      //shiftToShifter(1000);
      //setLedOn(i, j, 0, 0, 1, 0);
      //shiftToShifter(1000);
      //Serial.println("Currently displaying LED:");
      //Serial.print("x: ");
      //Serial.print(i);
      //Serial.print(" y: ");
      //Serial.print(j);
      //Serial.println();
      if(c == 0) {
      setLedOn(i, j, 1,0, 0, 0);
      } else if (c == 1) {
      setLedOn(i, j, 0,1, 0, 0);
      } else {
      setLedOn(i, j, 0,0,1, 0);
      }
      
    }
  }
  shiftToShifter(10000);
  }

}
