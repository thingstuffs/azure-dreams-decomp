#include "common.h"

/* If the referenced value is unset (via a1's indirect pointer field),
 * set the "used"/flag bit (0x8000) both on the 16-bit flags field located
 * one halfword before a0, and on the global 32-bit flags word D_800814A0.
 * Sibling of func_8004B530/func_8004B2E0 (code5.c, gcc 2.7.2 -O2 -G0
 * -fno-schedule-insns TU) which share the identical tail. */
typedef struct S_8004B298_a1 {
    s32 unk00;
    s32 *unk04;
} S_8004B298_a1;

extern int D_800814A0;

void func_8004B298(u16 *a0, S_8004B298_a1 *a1) {
    if (*a1->unk04 == 0) {
        a0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
