#include "common.h"

/* Returns 0 if a0 is NULL; otherwise finds the 1-based index of the first
 * 12-byte struct element (starting at a0) whose byte0 has bit 0x80 set
 * (via func_8004B4DC), reads the signed byte at offset+2 of that indexed
 * struct (i.e. a0 + idx*12 - 10), adds 0x80, and returns as a 16-bit value. */
typedef struct {
    /* 0x0 */ s8 unk0;
    /* 0x1 */ s8 pad1;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 pad2[9];
} S_8004A10C; /* size 0xC */

extern s32 func_8004B4DC(S_8004A10C *a0);

s16 func_8004A10C(S_8004A10C *a0) {
    s32 idx;
    s8 val;

    if (a0 == 0) {
        return 0;
    }
    idx = func_8004B4DC(a0);
    val = ((s8 *)a0)[idx * 12 - 10];
    return val + 0x80;
}
