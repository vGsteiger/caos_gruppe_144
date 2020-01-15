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
  int timer;
} star;

star starArray0[6];

/*
   Star animation which randomly spawns stars on the left and right and explodes them if they touch.
*/

struct star createStar() {
  star s;
  s.y = random(6);
  starColor c;
  c.r = random(2);
  c.g = random(2);
  c.b = random(2);
  s.color = c;
  s.timer = random(8);
  int ran = random(100);
  if (ran < 50) {
    s.direct = 1;
    s.x = 0;
  } else {
    s.direct = -1;
    s.x = 11;
  }
}

void starAnimation() {
  Serial.println("Star animation started");
  for (int i = 0; i < 6; i++) {
    starArray0[i] = createStar();
  }
  Serial.println("Stars created!");
  while (true) {
    for (int i = 0; i < 6; i++) {
      Serial.print("At star: ");
      Serial.println(i);
      Serial.print("Star has coord x: ");
      Serial.println(starArray0[i].x);
      Serial.print("Star has coord y: ");
      Serial.println(starArray0[i].y);
      runStar(starArray0[i], i);
      if (checkIRSensor()) {
        return;
      }
    }
    shiftToShifter(1000);
  }
}

void runStar(star s, int index) {
  if (s.timer == 0) {
    setLedOn(s.x, s.y, s.color.r, s.color.g, s.color.b, 0);
    areSameCoordinates(s, index);
    if (s.direct == 1) {
      s.x++;
      if (s.x > 11) {
        starArray0[index] = createStar();
      }
    } else {
      s.x--;
      if (s.x < 0) {
        starArray0[index] = createStar();
      }
    }
  } else {
    s.timer--;
    Serial.print("Star timer is: ");
    Serial.println(starArray0[index].timer);
  }
}

void areSameCoordinates(star s, int index) {
  for (int r = 0; r < 6; r++) {
    if (r == index) {
      continue;
    } else {
      star other = starArray0[r];
      if (other.x == s.x && other.y == s.x) {
        explodeStar(s);
        explodeStar(other);
        starArray0[r] = createStar();
        starArray0[index] = createStar();
      }
    }
  }
}

void explodeStar(star s) {
  starColor c = s.color;
  setLedOn(s.x, s.y, c.r, c.g, c.b, 0);
  setLedOn(s.x - 1, s.y - 1, c.r, c.g, c.b, 0);
  setLedOn(s.x + 1, s.y + 1, c.r, c.g, c.b, 0);
  setLedOn(s.x + 1, s.y - 1, c.r, c.g, c.b, 0);
  setLedOn(s.x - 1, s.y + 1, c.r, c.g, c.b, 0);
}
