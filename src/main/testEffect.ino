
void test()
{
  Serial.println("Testeffect runs!");
  char welcomeMsg[38] = "abcdefghijklmnopqrstuvwxyz0123456789";

  if (checkIRSensor()) {
    return;
  }
  printLetters(welcomeMsg);
}
