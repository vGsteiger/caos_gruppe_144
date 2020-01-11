
void test()
{

  char welcomeMsg[38] = "abc";
  if (checkIRSensor()) {
    return;
  }
  if (!printLetters(welcomeMsg)) {
    return;
  }
}
