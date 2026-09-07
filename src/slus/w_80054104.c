#include "common.h"

/* Copies an 8-byte lookup table (D_80032E0C, 4 halfwords) onto the stack, then for
   each i in [0, 0x30) and j in [0, 3) reads table[j], packs it with the high nibble
   of i into a byte code, asks func_8005405C(table[j]) whether that entry is
   "available", and if so forwards (code, region-offset) to func_80055730. */
typedef struct {
    s16 v[4];
} S_80032E0C;

extern S_80032E0C D_80032E0C;
extern s32 func_8005405C(s16 n);
extern void func_80055730();

void func_80054104(void) {
    S_80032E0C local;
    s32 i, j;
    s32 hi, base;
    s16 v;
    s32 val;

    local = D_80032E0C;
    i = 0;
    do {
        j = 0;
        hi = (u32)(i & 0xFF) >> 4;
        base = ((i & 0xF) << 10) + 0x1C00;
    inner:
        v = local.v[j];
        val = ((v << 8) & 0xFF00) | hi;
        if (v == 0) {
            val += 0x10;
        }
        if ((func_8005405C(v) << 16) != 0) {
            func_80055730(val, base);
        }
        j++;
        if (j < 3) {
            goto inner;
        }
        i++;
    } while (i < 0x30);
}
