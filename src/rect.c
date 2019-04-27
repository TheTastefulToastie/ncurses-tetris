#include "rect.h"

int rect_contains_point(rect_t r, int x, int y) {
  return (
    x >= r.x &&
    y >= r.y &&
    x <  r.x + r.w &&
    y <  r.y + r.h
  ) ? 1 : 0;
}
