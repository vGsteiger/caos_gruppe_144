
void test()
{
  for(int j = 0; j < 6; j++) {
  for(int i = 0; i < 12; i++) {
    setLedOn(i,j,0,1,0,0);
  }
  }
        shiftToShifter(1000);
  //setLedOn(5,0,0,0,1,0);
  //shiftToShifter(10000);
}
