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
} star;

struct star createStar(int layer) {
  star s;
  s.y = random(6);
  starColor c;
  c.r = random(2);
  c.g = random(2);
  c.b = random(2);
  s.color = c;
  int ran = random(100);
  if(ran < 50) {
    s.direct = 1;
    s.x = 0;
  } else {
    s.direct = -1;
    s.y = 11;
  }
}
