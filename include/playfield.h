#ifndef __PLAYFIELD_H__
#define __PLAYFIELD_H__

#include <stdint.h>
#include "rect.h"
#include "tetromino.h"

typedef struct playfield_t {
  rect_t rect;
  uint8_t *buffer;
} playfield_t;

playfield_t * playfield_create(int x, int y, int w, int h);
void          playfield_destroy(playfield_t *pf);
int           playfield_check_collision(playfield_t *pf, tetromino_t t);

#endif // __PLAYFIELD_H__
