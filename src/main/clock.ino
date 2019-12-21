/*
 * Simple clock output together with the real time clock, still has to be tested.
 */
void clockAnimation() {
  while(true) {
  DateTime now = rtc.now();
  char timeStamp[11];
  sprintf(timeStamp, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  printLetters(timeStamp);
  char date[13];
  sprintf(date, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  printLetters(date);
}
}
