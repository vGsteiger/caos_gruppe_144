typedef struct color {
  int r;
  int g;
  int b;
} color;

typedef struct rocket {
  int x;
  int y;
  color c;
  int timer;
  int maxHeight;
  int layer;
  boolean burnt;
} rocket;

boolean rocketInit = false;
rocket rocketArray[6];

void firework() {
  Serial.println("Rocket runs!");
  rocketInit = true;
  for (int i = 0; i < 6; i++) {
    rocketArray[i] = spawnRocket(0);
  }

  Serial.println("Rocket Running.");
  while (true) {
    for (int i = 0; i < 3; i++) {
      int currHeight = rocketArray[i].maxHeight;
      //for (int t = 0; t <= currHeight; t++) {
        if (checkIRSensor()) {
          return;
        }
        burnRocket(i);
      //}
    }
    shiftToShifter(500);
  }
}

struct rocket spawnRocket(int l) {
  rocket r;
  r.x = random(12);
  r.y = 0;
  color c;
  c.r = random(2);
  c.g = random(2);
  c.b = random(2);
  r.c = c;
  r.timer = 0;
  r.maxHeight = random(3, 5);
  r.layer = l;
  return r;
}

struct rocket explodeRocket(rocket r) {
  color c = r.c;
  setLedOn(r.x, r.y, c.r, c.g, c.b, r.layer);
  setLedOn(r.x - 1, r.y - 1, c.r, c.g, c.b, r.layer);
  setLedOn(r.x + 1, r.y + 1, c.r, c.g, c.b, r.layer);
  setLedOn(r.x + 1, r.y - 1, c.r, c.g, c.b, r.layer);
  setLedOn(r.x - 1, r.y + 1, c.r, c.g, c.b, r.layer);
  return spawnRocket(r.layer);
}

void burnRocket(int iterate) {
  rocket r = rocketArray[iterate];
  if (r.timer == r.maxHeight) {
    rocketArray[iterate] = explodeRocket(r);
    return;
  } else {
    color c = r.c;
    setLedOn(r.x, r.y, c.r, c.g, c.b, r.layer);
    r.y++;
    int ran = random(100);
    if (r.x < 10) {
      if (ran < 15) {
        r.x--;
      } else if (ran < 30) {
        r.x++;
      }
    }
    r.timer++;
    rocketArray[iterate] = r;
    return;
  }
}
