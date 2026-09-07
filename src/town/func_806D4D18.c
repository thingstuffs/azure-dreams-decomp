#include "common.h"

typedef struct {
    s32 values[3];
} ValueTriple;

typedef struct {
    ValueTriple first;
    volatile s32 last;
} ValueTable;

extern ValueTable D_80016028;
extern s32 func_80018868(s32, s32);

s32 func_80016D18(void) {
    ValueTable table;

    table = D_80016028;
    return ((s32 *)&table)[func_80018868(0x990, 2)];
}

/* MECHANISM: A whole 16-byte aggregate with a volatile final word splits into
   retail's 3+1 stack copy in the 0x28 frame. The callee's true two-argument ABI
   frees a2 as the sole held global base; cdk emits the split lui/addiu shape. */
