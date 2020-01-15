
void test()
{
  Serial.println("Testeffect runs!");
  char uniMsg[14] = "Uni Basel";
  printLetters(uniMsg);
  char welcomeMsg[38] = "abcdefghijklmnopqrstuvwxyz0123456789";

  if (checkIRSensor()) {
    return;
  }
  printLetters(welcomeMsg);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 12; j++) {
      setLedOn(j, i, 1, 0, 0, 0);
      shiftToShifter(300);
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 12; j++) {
      setLedOn(j, i, 0, 1, 0, 0);
      shiftToShifter(300);
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 12; j++) {
      setLedOn(j, i, 0, 0, 1, 0);
      shiftToShifter(300);
    }
  }
  return;
}
