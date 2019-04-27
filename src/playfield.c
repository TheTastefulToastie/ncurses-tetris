#include "playfield.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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
  for (block_t *b = t.blocks, *end = t.blocks + TETROMINO_NUM_BLOCKS; b != end; ++b)
    if (!rect_contains_point(pf->rect, pf->rect.x + t.x + b->x, pf->rect.y + t.y + b->y))
      return 1;
  return 0;
}
