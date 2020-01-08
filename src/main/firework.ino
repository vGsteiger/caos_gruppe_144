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

rocket rocketArray0[6];
//rocket rocketArray1[6];

void firework() {
  for (int i = 0; i < 6; i++) {
    rocketArray0[i] = spawnRocket(0);
    //rocketArray0[i] = spawnRocket(1);
  }
  Serial.println("New Spawn happened!");
  while (true) {
    if(checkIRSensor()){
        return;
    }
    for (int i = 0; i < 6; i++) {
      for(int t = 0; t <= rocketArray0[i].maxHeight; t++){
      burnRocket(i);
      //burnRocket(rocketArray1[i], i);
      shiftToShifter(1000);
      }
    }
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
  r.maxHeight = random(6);
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
  rocket r = rocketArray0[iterate];
  Serial.println("Current coordinates of rocket:");
  Serial.print("x: ");
  Serial.print(r.x);
  Serial.print(" y: ");
  Serial.print(r.y);
  Serial.println();
  Serial.println("Timer of Rocket:");
  Serial.print(r.timer);
  Serial.println();
  Serial.println("MaxHeigth of Rocket:");
  Serial.print(r.maxHeight);
  Serial.println();
  if (r.timer == r.maxHeight) {
      rocketArray0[iterate] = explodeRocket(r);
      return;
  } else {
    color c = r.c;
    setLedOn(r.x, r.y, c.r, c.g, c.b, r.layer);
    r.y++;
    int ran = random(100);
    if (r.x > 0 && r.x < 12) {
      if (ran < 15) {
        r.x--;
      } else if (ran < 30) {
        r.x++;
      }
    }
    r.timer++;
    rocketArray0[iterate] = r;
    return;
  }
}
