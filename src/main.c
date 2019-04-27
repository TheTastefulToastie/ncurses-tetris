#include <stdio.h>
#include "renderer.h"
#include "playfield.h"
#include "tetromino.h"

int main(int argc, char **argv) {
  renderer_init();
  renderer_clear();

  playfield_t *pf = playfield_create(2, 2, 10, 24);
  tetromino_t t   = tetromino_create(pf->rect.w * .5, 1, TETROMINO_Z_TYPE, pf);

  goto REDRAW;

  for (;;) {
    switch (renderer_get_key()) {
      case 'q': goto LABEL_EXIT;
      case 'h': case KEY_LEFT:  t = tetromino_move(t,-1, 0); goto RE_RENDER;
      case 'l': case KEY_RIGHT: t = tetromino_move(t, 1, 0); goto RE_RENDER;
      case 'j': case KEY_DOWN:  t = tetromino_move(t, 0, 1); goto RE_RENDER;
      case 'k': case KEY_UP:    t = tetromino_rotate(t, TETROMINO_COUNTER_CLOCKWISE); goto RE_RENDER;
      default : continue;
    }
REDRAW:
    renderer_draw_playfield(pf);
    renderer_draw_tetromino(t);
    renderer_present();
  }

LABEL_EXIT:
  renderer_deinit();
  playfield_destroy(pf);
  return 0;
}
