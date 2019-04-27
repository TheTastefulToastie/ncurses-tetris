#ifndef __TETROMINO_H__
#define __TETROMINO_H__

#define TETROMINO_NUM_BLOCKS 4

#define TETROMINO_O_TYPE 0
#define TETROMINO_I_TYPE 1
#define TETROMINO_T_TYPE 2
#define TETROMINO_L_TYPE 3
#define TETROMINO_J_TYPE 4
#define TETROMINO_S_TYPE 5
#define TETROMINO_Z_TYPE 6

#define TETROMINO_O_COLOR 0
#define TETROMINO_I_COLOR 1
#define TETROMINO_T_COLOR 2
#define TETROMINO_L_COLOR 3
#define TETROMINO_J_COLOR 4
#define TETROMINO_S_COLOR 5
#define TETROMINO_Z_COLOR 6

typedef struct playfield_t playfield_t;

typedef struct {
  int x, y; // The position relative to the tetromino
  int color;
} block_t;

typedef struct {
  int x, y;
  int type;
  playfield_t *pf;
  block_t blocks[TETROMINO_NUM_BLOCKS];
} tetromino_t;

tetromino_t tetromino_create(int x, int y, int type, playfield_t *pf);
tetromino_t tetromino_attach(tetromino_t t, playfield_t *pf);
tetromino_t tetromino_move(tetromino_t t, int offset_x, int offset_y);
tetromino_t tetromino_rotate(tetromino_t t, int dir);

#endif // __TETROMINO_H__
