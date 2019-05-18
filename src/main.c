#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "renderer.h"
#include "playfield.h"
#include "tetromino.h"

int main(int argc, char **argv) {
  srand(time(0));
  renderer_init();
  renderer_clear();

  playfield_t *pf = playfield_create(3, 2, 10, 24);
  tetromino_t  t  = tetromino_create(pf->rect.w * .5, 0, tetromino_get_random_type(), pf);

  goto REDRAW;

  for (;;) {
    switch (renderer_get_key()) {
      case 'q': goto LABEL_EXIT;
      case ' ':                 t = tetromino_drop(t);       goto REDRAW;
      case 'h': case KEY_LEFT:  t = tetromino_move(t,-1, 0); goto REDRAW;
      case 'l': case KEY_RIGHT: t = tetromino_move(t, 1, 0); goto REDRAW;
      case 'j': case KEY_DOWN:  t = tetromino_move(t, 0, 1); goto REDRAW;
      case 'k': case KEY_UP:    t = tetromino_rotate(t, TETROMINO_CLOCKWISE); goto REDRAW;
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
