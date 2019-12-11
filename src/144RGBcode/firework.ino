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
} rocket;

void firework(int seconds) {
  rocket rocketArray[10];
}

struct rocket spawnRocket(int l) {
  rocket r; 
  r.x = random(16);
  r.y = 0;
  color c;
  c.r = random(2);
  c.g = random(2);
  c.b = random(2);
  r.c = c;
  r.timer = random(30);
  r.maxHeight = random(6);
  r.layer = l;
  return r;
}

void explodeRocket(rocket r) {
  color c = r.c;
  setLedOn(r.x,r.y,c.r,c.g,c.b,r.layer);
}
