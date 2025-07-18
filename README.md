A set of amateur Sudoku solvers implemented with features from C23 and C2Y standard.
 - `brute_force.c`: Use `_BitInt()` to encode constraints of the entire board in a single integer.
 - `graph_color.c`: Use `<stdbit.h>` to decode constraint bitmasks of each cell.
 - `16x16_embed/puzzle.h`: Use `#embed` to load board in a file in compile-time.
 - `_c2y.c` variants: `if` declaration and named loop.

Subgrid can be any rectangular as long as `(X*Y)<=61`, board size is implicitly `(X*Y)*(Y*X)`.

## Building

`cc -O2 -std=c23 {pick-algo}.c -I ./{pick-board} -o out && ./out`

Compiler/libc requirements:
 - `<stdbit.h>`: `glibc` v2.39+
 - `constexpr`: `gcc-14`, `clang-19`, `slimcc`
 - `#embed`: `gcc-15`, `clang-19`, `slimcc`
 - `if` declaration and named loop: `gcc-15`, `slimcc`
