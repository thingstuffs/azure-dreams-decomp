#include "common.h"

typedef struct {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    s16 fieldA;
} Entry;

extern s32 func_800A6D30(void);

void func_8001CCEC(s16 arg0, s16 *arg1, s16 *arg2, Entry *arg3) {
    if (arg3->fieldA == 0) {
        *arg1 = 0;
        *arg2 = 0;
        return;
    }

    switch (arg0) {
    case 0:
        *arg1 = arg3->field4;
        *arg2 = ((u16)func_800A6D30() % (arg3->field6 - 2)) + 1;
        break;

    case 2:
        *arg1 = ((u16)func_800A6D30() % (arg3->field4 - 2)) + 1;
        *arg2 = arg3->field6;
        break;

    case 4:
        *arg1 = -1;
        *arg2 = ((u16)func_800A6D30() % (arg3->field6 - 2)) + 1;
        break;

    default:
        *arg1 = ((u16)func_800A6D30() % (arg3->field4 - 2)) + 1;
        *arg2 = -1;
        break;
    }
}

/* MECHANISM: The two output pointers and record pointer stay live across RNG calls,
   naturally producing the retail s1/s2/s0 hold set and 0x20-byte frame.
   Each mode selects a copy/random/-1 pair using exact halfword field widths. */
