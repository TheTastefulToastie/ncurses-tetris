#include <stddef.h>
#include "tetromino.h"
#include "playfield.h"


tetromino_t tetromino_create(int x, int y, int type, playfield_t *pf) {
  tetromino_t t;
  t.x    = x;
  t.y    = y;
  t.pf   = pf;
  t.type = type;

  switch (type) {

    case TETROMINO_O_TYPE:
      t.blocks[0] = (block_t){ 0, 0, TETROMINO_O_COLOR };
      t.blocks[1] = (block_t){ 1, 0, TETROMINO_O_COLOR };
      t.blocks[2] = (block_t){ 0, 1, TETROMINO_O_COLOR };
      t.blocks[3] = (block_t){ 1, 1, TETROMINO_O_COLOR };
      break;

    case TETROMINO_I_TYPE:
      t.blocks[0] = (block_t){-1, 0, TETROMINO_I_COLOR };
      t.blocks[1] = (block_t){ 0, 0, TETROMINO_I_COLOR };
      t.blocks[2] = (block_t){ 1, 0, TETROMINO_I_COLOR };
      t.blocks[3] = (block_t){ 2, 0, TETROMINO_I_COLOR };
      break;

    case TETROMINO_T_TYPE:
      t.blocks[0] = (block_t){-1, 0, TETROMINO_T_COLOR };
      t.blocks[1] = (block_t){ 0, 0, TETROMINO_T_COLOR };
      t.blocks[2] = (block_t){ 1, 0, TETROMINO_T_COLOR };
      t.blocks[3] = (block_t){ 0, 1, TETROMINO_T_COLOR };
      break;

    case TETROMINO_L_TYPE:
      t.blocks[0] = (block_t){-1, 0, TETROMINO_L_COLOR };
      t.blocks[1] = (block_t){ 0, 0, TETROMINO_L_COLOR };
      t.blocks[2] = (block_t){ 1, 0, TETROMINO_L_COLOR };
      t.blocks[3] = (block_t){-1, 1, TETROMINO_L_COLOR };
      break;

    case TETROMINO_J_TYPE:
      t.blocks[0] = (block_t){-1, 0, TETROMINO_J_COLOR };
      t.blocks[1] = (block_t){ 0, 0, TETROMINO_J_COLOR };
      t.blocks[2] = (block_t){ 1, 0, TETROMINO_J_COLOR };
      t.blocks[3] = (block_t){ 1, 1, TETROMINO_J_COLOR };
      break;

    case TETROMINO_S_TYPE:
      t.blocks[0] = (block_t){ 0, 0, TETROMINO_S_COLOR };
      t.blocks[1] = (block_t){ 1, 0, TETROMINO_S_COLOR };
      t.blocks[2] = (block_t){ 0, 1, TETROMINO_S_COLOR };
      t.blocks[3] = (block_t){-1, 1, TETROMINO_S_COLOR };
      break;

    case TETROMINO_Z_TYPE:
      t.blocks[0] = (block_t){-1, 0, TETROMINO_Z_COLOR };
      t.blocks[1] = (block_t){ 0, 0, TETROMINO_Z_COLOR };
      t.blocks[2] = (block_t){ 0, 1, TETROMINO_Z_COLOR };
      t.blocks[3] = (block_t){ 1, 1, TETROMINO_Z_COLOR };
      break;

  }

  return t;
}

tetromino_t tetromino_attach(tetromino_t t, playfield_t *pf) {
  tetromino_t new_t = t;
  t.pf = pf;
  return new_t;
}

tetromino_t tetromino_move(tetromino_t t, int offset_x, int offset_y) {
  tetromino_t new_t = t;
  new_t.x += offset_x;
  new_t.y += offset_y;
  return (t.pf != NULL && playfield_check_collision(new_t.pf, new_t)) ? t : new_t;
}

tetromino_t tetromino_rotate(tetromino_t t, int dir) {
  tetromino_t new_t = t;

  for (block_t *b = new_t.blocks, *end = new_t.blocks + TETROMINO_NUM_BLOCKS; b != end; ++b) {
    int x = b->x, y = b->y;
    b->x = -y * dir;
    b->y =  x * dir;
  }

  return (t.pf != NULL && playfield_check_collision(new_t.pf, new_t)) ? t : new_t;
}
