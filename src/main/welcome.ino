void welcomeAnimation() {
  char welcomeMsg[28] = "Uni Basel CAOS Projekt 2019";
  if(checkIRSensor()){
        return;
  }
  printLetters(welcomeMsg);
}
