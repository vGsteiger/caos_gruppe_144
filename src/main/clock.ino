/*
   Simple clock output together with the real time clock, still has to be tested.
*/
void clockAnimation() {
  while (true) {
    tmElements_t tm;
    if (RTC.read(tm)) {
      char timeStamp[16];

      sprintf(timeStamp, "%02d:%02d:%02d", tm.Hour + 1, tm.Minute, tm.Second);
      if (checkIRSensor()) {
        return;
      }
      //Serial.println(timeStamp);
      if (!printLetters(timeStamp)) {
        return;
      }
      char date[16];
      sprintf(date, "%02d/%02d/%04d", tm.Day, tm.Month, tmYearToCalendar(tm.Year));
      if (checkIRSensor()) {
        return;
      }
      if (!printLetters(date)) {
        return;
      }
    } else {
      if (RTC.chipPresent()) {
        Serial.println("The DS1307 is stopped.  Please run the SetTime");
        Serial.println("example to initialize the time and begin running.");
        Serial.println();
      } else {
        Serial.println("DS1307 read error!  Please check the circuitry.");
        Serial.println();
      }
      delay(9000);
    }



  }
}
