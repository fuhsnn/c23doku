A set of amateur Sudoku solvers implemented with features from C23 standard.
 - `brute_force.c`: Use `_BitInt()` to encode constraints of the entire board in a single integer.
 - `graph_color.c`: Use `<stdbit.h>` to decode constraint bitmasks of each cell.
 - `16x16_embed/puzzle.h`: Use `#embed` to load board in a file in compile-time.

Subgrid can be any rectangular as long as `X*Y<=61`, board size is implicitly `(X*Y)*(Y*X)`. 

## Building

`cc -O2 -std=c23 {pick-algo}.c -I ./{pick-board} -o out && ./out`

The latest (2024) c-toolchain is required, only `clang-19` with `glibc 2.39` can build all combinations. `gcc-14` lacks `#embed` but otherwise work.
