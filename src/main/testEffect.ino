
void test()
{
 for(int i = 0; i < 6; i++) {
      setLedOn(11,i,1,0,0,0);
      shiftToShifter(1000);
      setLedOn(11,i,0,1,0,0);
      shiftToShifter(1000);
      setLedOn(11,i,0,0,1,0);
      shiftToShifter(1000);
  }
}
