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
} oneStar;

oneStar starArray0[6];

/*
   Star animation which randomly spawns stars on the left and right and explodes them if they touch.
*/

struct star createStar() {
  oneStar s;
  s.y = random(0,6);
  starColor c;
  c.r = random(0,2);
  c.g = random(0,2);
  c.b = random(0,2);
  s.color = c;
  s.timer = random(0,10);
  int ran = random(0,100);
  if (ran < 50) {
    s.direct = 1;
    s.x = 0;
  } else {
    s.direct = -1;
    s.x = 11;
  }
  return s;
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
      runStar(i);
      if (checkIRSensor()) {
        return;
      }
    }
    shiftToShifter(1000);
  }
}

void runStar(int index) {
  if (starArray0[index].timer == 0) {
    setLedOn(starArray0[index].x, starArray0[index].y, starArray0[index].color.r, starArray0[index].color.g, starArray0[index].color.b, 0);
    areSameCoordinates(index);
    if (starArray0[index].direct == 1) {
      starArray0[index].x++;
      if (starArray0[index].x > 11) {
        starArray0[index] = createStar();
      }
    } else {
      starArray0[index].x--;
      if (starArray0[index].x < 0) {
        starArray0[index] = createStar();
      }
    }
  } else {
    starArray0[index].timer--;
    Serial.print("Star timer is: ");
    Serial.println(starArray0[index].timer);
  }
}

void areSameCoordinates(int index) {
  for (int r = 0; r < 6; r++) {
    if (r == index) {
      continue;
    } else {
      star other = starArray0[r];
      if (other.x == starArray0[index].x && other.y == starArray0[index].y && other.x != 0 && other.x != 11) {
        explodeStar(starArray0[index]);
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
