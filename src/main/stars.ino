typedef struct starColor {
  int r;
  int g;
  int b;
} starColor;

typedef struct star {
  int x;
  int y;
  int direct; // 1 = from left to right, -1 = from right to left
  starColor color;
  unsigned long timestamp;
  int timer;
  int layer;
} star;

star starArray0[6];
//star starArray1[6];

/*
   Star animation which randomly spawns stars on the left and right and explodes them if they touch.
*/

struct star createStar(int layer) {
  star s;
  s.y = random(6);
  starColor c;
  c.r = random(2);
  c.g = random(2);
  c.b = random(2);
  s.color = c;
  s.timer = random(10);
  int ran = random(100);
  s.layer = layer;
  if (ran < 50) {
    s.direct = 1;
    s.x = 0;
  } else {
    s.direct = -1;
    s.x = 11;
  }
  decrementTimer(s);
}

void starAnimation() {
  Serial.println("Star animation started");
  for (int i = 0; i < 6; i++) {
    starArray0[i] = createStar(0);
    //starArray1[i] = createStar(1);
  }
  Serial.println("Stars created!");
  while (true) {
    for (int i = 0; i < 6; i++) {
      runStar(starArray0[i], i);
      Serial.print("Star timer is: ");
      Serial.println(starArray0[i].timer);
      //runStar(starArray1[i], i);
      if (checkIRSensor()) {
        return;
      }
    }
    shiftToShifter(1000);
  }
}

void runStar(star s, int index) {
  if (s.timer == 0) {
    setLedOn(s.x, s.y, s.color.r, s.color.g, s.color.b, s.layer);
    areSameCoordinates(s, index);
    if (s.direct == 1) {
      s.x++;
      if (s.x > 11) {
        starArray0[index] = createStar(0);
      }
    } else {
      s.x--;
      if (s.x < 0) {
        starArray0[index] = createStar(0);
      }
    }
  }
}

void areSameCoordinates(star s, int index) {
  if (s.layer == 0) {
    for (int r = 0; r < 6; r++) {
      if (r == index) {
        continue;
      } else {
        star other = starArray0[r];
        if (other.x == s.x && other.y == s.x) {
          explodeStar(s);
          explodeStar(other);
          starArray0[r] = createStar(s.layer);
          starArray0[index] = createStar(s.layer);
        }
      }
    }
  } else {
    for (int r = 0; r < 6; r++) {
      if (r == index) {
        continue;
      } else {
        //star other = starArray1[r];
        //if (other.x == s.x && other.y == s.x) {
        //explodeStar(s);
        //explodeStar(other);
        //starArray1[r] = createStar(s.layer);
        //starArray1[index] = createStar(s.layer);
      }
    }
  }
}

void explodeStar(star s) {
  starColor c = s.color;
  setLedOn(s.x, s.y, c.r, c.g, c.b, s.layer);
  setLedOn(s.x - 1, s.y - 1, c.r, c.g, c.b, s.layer);
  setLedOn(s.x + 1, s.y + 1, c.r, c.g, c.b, s.layer);
  setLedOn(s.x + 1, s.y - 1, c.r, c.g, c.b, s.layer);
  setLedOn(s.x - 1, s.y + 1, c.r, c.g, c.b, s.layer);
}

void decrementTimer(star s) {
  while (s.timer != 0) {
    s.timestamp = millis();
    if(millis() - s.timestamp > 1000) {
    s.timer--;
    }
  }
}
