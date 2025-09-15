#include "all.h"
#include <stdbit.h>

typedef uint64_t Mask;

typedef struct {
  int x, y, b;
  Mask state;
  Mask init;
} Cell;

static bool interfere(Cell *a, Cell *b) {
  return a->x == b->x || a->y == b->y || a->b == b->b;
}

int main() {
  int cell_count = 0;
  Cell cells[total];

  for (int y = 0; y < digit; y++)
    for (int x = 0; x < digit; x++) {
      int num = encode_num(&puzzle[x + y * digit]);
      if ((num < 0) || (num >= digit))
        cells[cell_count++] = (Cell){.x = x, .y = y, .b = box_id(x, y)};
    }

  if (!cell_count)
    error_quit("no fillable cell");

  for (int y = 0; y < digit; y++)
    for (int x = 0; x < digit; x++) {
      int num = puzzle[x + y * digit];
      if ((num < 0) || (num >= digit))
        continue;

      int b = box_id(x, y);
      Mask m = (Mask){1} << num;
      static Mask vx[digit], vy[digit], vb[digit];

      if (vx[x] & m || vy[y] & m || vb[b] & m)
        error_quit("invalid puzzle");
      vx[x] |= m;
      vy[y] |= m;
      vb[b] |= m;

      for (Cell *p = &cells[0]; p != &cells[cell_count]; p++)
        if (interfere(p, &(Cell){.x = x, .y = y, .b = b})) {
          p->init |= m;
          if (stdc_count_ones(p->init) == (digit))
            error_quit("invalid puzzle");
        }
    }

  auto first = &cells[0];
  for (Cell *p = first; p != &cells[cell_count]; p++) {
    p->state = p->init;
    if (stdc_count_ones(first->state) < stdc_count_ones(p->state))
      first = p;
  }
  Cell tmp = cells[0];
  cells[0] = *first;
  *first = tmp;

  for (int idx = 0;;) {
    int sort_count[digit] = {};
    bool backtrack = false;

    for (Cell *p = &cells[idx + 1]; p != &cells[cell_count]; p++) {
      Cell c = cells[idx];
      if (interfere(p, &c)) {
        p->state |= (Mask){1} << stdc_trailing_ones(c.state);

        if (stdc_count_ones(p->state) == digit) {
          backtrack = true;
          break;
        }
      }
      sort_count[digit - 1 - stdc_count_ones(p->state)]++;
    }

    if (!backtrack) {
      int accum = 0;
      for (int i = 0; i < digit; i++) {
        accum += sort_count[i];
        sort_count[i] = accum - 1;
      }
      static Cell sort_buf[total];
      for (int i = idx + 1; i < cell_count; i++) {
        Cell c = cells[i];
        sort_buf[sort_count[digit - 1 - stdc_count_ones(c.state)]--] = c;
      }
      int count = 0;
      for (int i = idx + 1; i < cell_count; i++)
        cells[i] = sort_buf[count++];

      if (++idx == cell_count)
        break;
      continue;
    }

    while (stdc_count_ones(cells[idx].state) == digit - 1)
      if (--idx < 0)
        error_quit("unsolvable\n");

    cells[idx].state |= cells[idx].state + 1;

    for (Cell *p = &cells[idx + 1]; p != &cells[cell_count]; p++) {
      p->state = p->init;

      for (int i = 0; i < idx; i++) {
        Cell c = cells[i];
        if (interfere(p, &c))
          p->state |= (Mask){1} << stdc_trailing_ones(c.state);
      }
    }
    continue;
  }

  for (int i = 0; i < cell_count; i++) {
    Cell c = cells[i];
    puzzle[c.x + c.y * digit] = stdc_trailing_ones(c.state);
  }

  print_puzzle();
  return 0;
}
