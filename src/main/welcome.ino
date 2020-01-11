void welcomeAnimation() {
  char welcomeMsg[29] = "Uni Basel CAOS Projekt 2019 ";
  if (checkIRSensor()) {
    return;
  }
  if (!printLetters(welcomeMsg)) {
    return;
  }
}
