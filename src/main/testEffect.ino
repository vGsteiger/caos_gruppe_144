
void test()
{

  char welcomeMsg[38] = "abc";
  if (checkIRSensor()) {
    return;
  }
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 12; j++) {
      setLedOn(j,i,1,0,0,0);
      shiftToShifter(1000);
    }
  }
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 12; j++) {
      setLedOn(j,i,0,1,0,0);
      shiftToShifter(1000);
    }
  }
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 12; j++) {
      setLedOn(j,i,0,0,1,0);
      shiftToShifter(1000);
    }
  }
  //if (!printLetters(welcomeMsg)) {
  //  return;
  //}
}
