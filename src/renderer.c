#include "renderer.h"

void renderer_init() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
}

void renderer_deinit() {
  endwin();
}

void renderer_present() {
  refresh();
}

void renderer_clear() {
  clear();
}

void renderer_draw_char(int x, int y, wchar_t *wc) {
  cchar_t cc;
  setcchar(&cc, wc, WA_NORMAL, 3, NULL);
  mvadd_wch(y, x, &cc);
}

void renderer_draw_rect(rect_t r) {
  for (int y = r.y; y < r.y + r.h; ++y)
    for (int x = r.x; x < r.x + r.w; ++x)
      renderer_draw_char(x, y, L"\u2591");
}

void renderer_draw_rect_outline(rect_t r, int line_type, int padding) {
  r.x -= padding;
  r.y -= padding;
  r.w += padding * 2;
  r.h += padding * 2;

  wchar_t *horizontal, *vertical, *corner_tl, *corner_tr, *corner_bl, *corner_br;

  switch (line_type) {

    case LINE_NORMAL:
      horizontal = L"\u2500";
      vertical   = L"\u2502";
      corner_tl  = L"\u250C";
      corner_tr  = L"\u2510";
      corner_bl  = L"\u2514";
      corner_br  = L"\u2518";
      break;

    case LINE_BOLD:
      horizontal = L"\u2501";
      vertical   = L"\u2503";
      corner_tl  = L"\u250F";
      corner_tr  = L"\u2513";
      corner_bl  = L"\u2517";
      corner_br  = L"\u251B";
      break;

    case LINE_DOTTED:
      horizontal = L"\u2508";
      vertical   = L"\u250A";
      corner_tl  = L"\u2577";
      corner_tr  = L"\u2577";
      corner_bl  = L"\u2575";
      corner_br  = L"\u2575";
      break;

    case LINE_DASHED:
      horizontal = L"\u2504";
      vertical   = L"\u2506";
      corner_tl  = L"\u2577";
      corner_tr  = L"\u2577";
      corner_bl  = L"\u2575";
      corner_br  = L"\u2575";
      break;

    case LINE_DOTTED_BOLD:
      horizontal = L"\u2509";
      vertical   = L"\u250B";
      corner_tl  = L"\u257B";
      corner_tr  = L"\u257B";
      corner_bl  = L"\u2579";
      corner_br  = L"\u2579";
      break;

    case LINE_DASHED_BOLD:
      horizontal = L"\u2505";
      vertical   = L"\u2507";
      corner_tl  = L"\u257B";
      corner_tr  = L"\u257B";
      corner_bl  = L"\u2579";
      corner_br  = L"\u2579";
      break;

    case LINE_DOUBLE:
      horizontal = L"\u2550";
      vertical   = L"\u2551";
      corner_tl  = L"\u2554";
      corner_tr  = L"\u2557";
      corner_bl  = L"\u255A";
      corner_br  = L"\u255D";
      break;

    case LINE_ROUNDED:
      horizontal = L"\u2500";
      vertical   = L"\u2502";
      corner_tl  = L"\u256D";
      corner_tr  = L"\u256E";
      corner_bl  = L"\u2570";
      corner_br  = L"\u256F";
      break;

  }

  for (int x = r.x + 1; x < r.x + r.w - 1; ++x) {
    renderer_draw_char(x, r.y          , horizontal);
    renderer_draw_char(x, r.y + r.h - 1, horizontal);
  }

  for (int y = r.y + 1; y < r.y + r.h - 1; ++y) {
    renderer_draw_char(r.x          , y, vertical);
    renderer_draw_char(r.x + r.w - 1, y, vertical);
  }

  renderer_draw_char(r.x          , r.y          , corner_tl);
  renderer_draw_char(r.x + r.w - 1, r.y          , corner_tr);
  renderer_draw_char(r.x          , r.y + r.h - 1, corner_bl);
  renderer_draw_char(r.x + r.w - 1, r.y + r.h - 1, corner_br);
}

void renderer_draw_playfield(playfield_t *pf) {
  renderer_draw_rect(pf->rect);
  renderer_draw_rect_outline(pf->rect, LINE_DOUBLE, 1);
  int w = pf->rect.w;
  for (int end_y = pf->rect.h, y = 0; y < end_y; ++y)
    for (int end_x = pf->rect.w, x = 0; x < end_x; ++x)
      if (pf->buffer[y * w + x])
        renderer_draw_char(pf->rect.x + x, pf->rect.y + y, L"\u2593");
}

void renderer_draw_tetromino(tetromino_t t) {
  if (t.pf != NULL) {
    t.x += t.pf->rect.x;
    t.y += t.pf->rect.y;
  }
  for (block_t *b = t.blocks, *end = t.blocks + TETROMINO_NUM_BLOCKS; b != end; ++b)
    renderer_draw_char(t.x + b->x, t.y + b->y, L"\u2593");
}

int renderer_get_key() {
  return getch();
}
