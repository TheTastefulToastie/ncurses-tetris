#ifndef __RENDERER_H__
#define __RENDERER_H__

#define _XOPEN_CURSES
#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <locale.h>
#include "rect.h"
#include "playfield.h"
#include "tetromino.h"

#define LINE_NORMAL      0
#define LINE_BOLD        1
#define LINE_DOTTED      2
#define LINE_DASHED      3
#define LINE_DOTTED_BOLD 4
#define LINE_DASHED_BOLD 5
#define LINE_DOUBLE      6
#define LINE_ROUNDED     7

void renderer_init();
void renderer_deinit();
void renderer_present();
void renderer_clear();
void renderer_draw_char(int x, int y, wchar_t *wc);
void renderer_draw_rect(rect_t r);
void renderer_draw_rect_outline(rect_t r, int line_type, int padding);
void renderer_draw_playfield(playfield_t *pf);
void renderer_draw_tetromino(tetromino_t t);
int  renderer_get_key();

#endif // __RENDERER_H__
