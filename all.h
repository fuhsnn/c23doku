#include <stdbit.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "puzzle.h"

constexpr int digit = box_x * box_y;
constexpr int total = digit * digit;

static_assert(box_x > 0);
static_assert(box_y > 0);
static_assert(digit <= 61);
static_assert(sizeof(puzzle) >= digit);

static int encode_num(char *c) {
  if (*c >= '1' && *c <= '9')
    return *c -= '1';
  if (*c >= 'A' && *c <= 'Z')
    return *c -= ('A' - 9);
  if (*c >= 'a' && *c <= 'z')
    return *c -= ('a' - 35);
  return *c = -1;
}

static char decode_num(int num) {
  if (num >= 0) {
    if (num < 9)
      return num + '1';
    if (num < 35)
      return num + ('A' - 9);
    if (num < 61)
      return num + ('a' - 35);
  }
  return '?';
}

static int box_id(int x, int y) {
  return (x / box_x) + (y / box_y) * box_y;
}

[[noreturn]]
static void error_quit(const char *s) {
  printf("%s\n", s);
  exit(1);
}

static void print_puzzle() {
  for (int y = 0; y < digit; y++) {
    for (int x = 0; x < digit; x++)
      printf("%c", decode_num(puzzle[x + y * digit]));
    printf("\n");
  }
}
