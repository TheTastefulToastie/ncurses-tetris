#ifndef __RECT_H__
#define __RECT_H__

typedef struct {
  int x, y, w, h;
} rect_t;

int rect_contains_point(rect_t r, int x, int y);

#endif // __RECT_H__
