
  void test()
  {
    for(int i = 0; i < 3; i++) {
      setLedOn(i,0,1,0,0,1);
      shiftToShifter(1000);
      setLedOn(i,0,1,0,0,0);
      shiftToShifter(1000);
    }
  }
