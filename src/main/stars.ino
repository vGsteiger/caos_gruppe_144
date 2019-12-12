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
star starArray1[6];

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
  if(ran < 50) {
    s.direct = 1;
    s.x = 0;
  } else {
    s.direct = -1;
    s.y = 11;
  }
}

void starAnimation(int seconds) {
  for(int i = 0; i < 6; i++) {
    starArray0[i] = createStar(0);
    starArray1[i] = createStar(1);
  }
  for(int t = 0; t < seconds; t++) {
    for(int i = 0; i < 6; i++) {
      runStar(starArray0[i],i);
      runStar(starArray1[i],i);
    }
  }
}

void runStar(star s, int index) {
  if(s.timer == 0) {
    setLedOn(s.x,s.y,s.c.r,s.c.g,s.c.b,s.layer);
    if(s.x + 1 == 16 && s.x - 1 == -1) {
        if(s.layer == 0) {
          starArray0[index] = createStar(0);
        } else {
          starArray1[index] = createStar(0);
        }
    }
    if(s.direct == 1) {
      s.x++;
    } else {
      s.x--;
    }
  } else {
    s.timer--;
  }
}

struct star areSameCoordinates(star.s; int layer, int index) {
  if(layer == 0) {
    for(int r = 0; r < 6; r++) {
      if(r == index) {
      continue;
      } else {
        star other = starArray0[r];
        //if()
      }
    }
  } else {
    
  }
}
