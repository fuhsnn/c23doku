#include "all.h"

typedef _BitInt(total * 3) State;

typedef struct {
  int x, y, b, num;
} Cell;

static State make_mask(Cell c) {
  unsigned _BitInt(total) bit = 1;
  State msk;
  msk = bit << (c.num * digit + c.x); // (num is filled at column[x])
  msk <<= total;
  msk |= bit << (c.num * digit + c.y); // (num is filled at row[y])
  msk <<= total;
  msk |= bit << (c.num * digit + c.b); // (num is filled at block[id])
  return msk;
}

int main() {
  State state = 0;
  int cell_count = 0;
  Cell cells[total] = {};

  for (int y = 0; y < digit; y++) {
    for (int x = 0; x < digit; x++) {
      int num = encode_num(&puzzle[x + y * digit]);
      if ((num < 0) || (num >= digit)) {
        cells[cell_count++] = (Cell){x, y, box_id(x, y)};
        continue;
      }
      State msk = make_mask((Cell){x, y, box_id(x, y), num});
      if (msk & state)
        error_quit("invalid puzzle\n");
      state |= msk;
    }
  }
  if (!cell_count)
    error_quit("no fillable cell");

  for (int idx = 0;;) {
    State msk = make_mask(cells[idx]);
    if (!(state & msk)) {
      if (++idx == cell_count)
        break;
      state |= msk;
      cells[idx].num = 0;
      continue;
    }

    while (++cells[idx].num >= digit) {
      if (--idx < 0)
        error_quit("unsolvable\n");
      state ^= make_mask(cells[idx]);
    }
  }

  for (int i = 0; i < cell_count; i++) {
    Cell c = cells[i];
    puzzle[c.x + c.y * digit] = c.num;
  }

  print_puzzle();
  return 0;
}
