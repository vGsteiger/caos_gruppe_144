void rollCredits() {
  char credits[60] = "Made by: Joey Zgraggen. Moritz Wuerth and Viktor Gsteiger ";
  if (checkIRSensor()) {
    return;
  }
  if (!printLetters(credits)) {
    return;
  }
}
