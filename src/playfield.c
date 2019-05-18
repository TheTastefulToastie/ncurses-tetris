#include "playfield.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

playfield_t * playfield_create(int x, int y, int w, int h) {
  playfield_t *ptr = malloc(sizeof *ptr);
  if (ptr == NULL) {
    printf("Failed to create playfield.\n");
    return NULL;
  }
  ptr->rect = (rect_t){ x, y, w, h };
  ptr->buffer = calloc(w * h, sizeof(ptr->buffer[0]));
  if (ptr->buffer == NULL) {
    printf("Failed to allocate buffer for playfield.\n");
    free(ptr);
    return NULL;
  }
  return ptr;
}

void playfield_destroy(playfield_t *pf) {
  free(pf->buffer);
  free(pf);
}

int playfield_check_collision(playfield_t *pf, tetromino_t t) {
  int x, y, w = pf->rect.w;
  for (block_t *b = t.blocks, *end = t.blocks + TETROMINO_NUM_BLOCKS; b != end; ++b) {
    x = t.x + b->x;
    y = t.y + b->y;
    if (!rect_contains_point(pf->rect, pf->rect.x + x, pf->rect.y + y) || pf->buffer[x + y * w])
      return 1;
  }
  return 0;
}

void playfield_place_tetromino(playfield_t *pf, tetromino_t t) {
  int x, y, w = pf->rect.w;
  for (block_t *b = t.blocks, *end = t.blocks + TETROMINO_NUM_BLOCKS; b != end; ++b) {
    x = b->x + t.x;
    y = b->y + t.y;
    pf->buffer[x + y * w] = b->color;
  }
  playfield_clear_complete_rows(pf);
}

int playfield_clear_complete_rows(playfield_t *pf) {
  int count = 0;
  int w = pf->rect.w;
  uint8_t *floor = pf->buffer + w * (pf->rect.h - 1);
  uint8_t *row = floor;
  for (int i = pf->rect.h; i--;) {
    int complete = 1;
    for (uint8_t *end = row + w, *b = row; b != end; ++b) {
      if (!*b) {
        complete = 0;
        break;
      }
    }
    if (complete) {
      memset(row, 0, w);
      count++;
    } else {
      memcpy(floor, row, w);
      floor -= w;
    }
    row -= w;
  }
  return count;
}
