#include "common.h"

typedef struct Box {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    s32 h;
    s32 d;
} Box;

s32 func_8008FD9C(Box *a, Box *b, Box *c, Box *e)
{
    s32 lo;
    s32 hi;

    if ((lo = b->x + a->x, hi = e->x + c->x, hi + c->w >= lo) && lo + a->w >= hi &&
        (lo = b->y + a->y, hi = e->y + c->y, hi + c->h >= lo) && lo + a->h >= hi &&
        (lo = b->z + a->z, hi = e->z + c->z, hi + c->d >= lo) && lo + a->d >= hi) {
        return 1;
    }
    return 0;
}

/* MECHANISM: frameless leaf. ONE six-term `&&` chain returning 1, with a single
   trailing `return 0` -- NOT six early `return 0;` statements. The && chain gives
   the false-target block SIX predecessors, which is what suppresses gcc's
   jump.c store-flag canonicalization (`slt;xori` + `j`) on the last term; the
   six branches each then get `move $v0,$zero` copied into their delay slot, and
   the final term keeps its `beqz / addiu $v0,$zero,1 / move $v0,$zero` pair with
   the compare demoted to $v1 because $v0 is live-out.
   Per-axis `lo`/`hi` are re-assigned via the comma operator INSIDE the chain so
   short-circuit order pins retail's load order (b,a then e,c,c->w); hoisting them
   to statements before the `if` reorders the first axis' loads. */
