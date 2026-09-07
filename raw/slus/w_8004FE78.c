#include "common.h"

/* For each of the 3 handles embedded at a0+0x24 (skipping zero entries), calls func_8001832C(handle). Then sets the 0x8000 "used" bit both on the 16-bit flags field at a0+0x1E and on the global flags word D_800814A0. No-op if a0 is NULL. */
/* Canonical global flags word shared by several sibling functions in this
 * TU family (code9.c, code10.c, code11.c, code5.c, w_8004F558.c, ...).
 * w_8004F558.c (same D_800814A0 |= 0x8000 tail as this function) declares
 * it as a plain `extern int` and matches with the address recomputed
 * TWICE (load then store, in different registers) -- follow that. */
extern int D_800814A0;

/* Entity struct as seen by func_8004FE78: a 16-bit flags field at 0x1E and
 * an embedded sub-object at 0x20 (same sub-object base referenced by
 * func_8004FF00 in this TU) whose second word (a 3-element id/handle
 * array starting at 0x24) is walked here. */
typedef struct S_8004FE78_a0 {
    u8 pad00[0x1E];
    u16 field_1E;   /* 0x1E */
    u8 pad20[0x24 - 0x20];
    s32 unk24[3];   /* 0x24, 0x28, 0x2C */
} S_8004FE78_a0;

extern void func_8001832C(s32 arg0);

void func_8004FE78(S_8004FE78_a0 *a0)
{
    s32 i;
    s32 *p;

    if (a0 != 0) {
        i = 0;
        p = (s32 *)((char *)a0 + 0x20);
        for (; i < 3; i++) {
            if (p[1] != 0) {
                func_8001832C(p[1]);
            }
            p++;
        }
        a0->field_1E |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
