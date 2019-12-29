
void test()
{
  if(checkIRSensor()){
      return;
  }
  //for(int i = 0; i < 5; i++) {
  setLedOn(3, 0, 1, 0, 0, 0);
  shiftToShifter(100);
  setLedOn(3, 0, 0, 1, 0, 0);
  shiftToShifter(100);
  setLedOn(3, 0, 0, 0, 1, 0);
  shiftToShifter(100);
  //}
}
