#include "common.h"

extern s32 D_80018FB4;
extern s32 D_80018FB8;
extern s32 D_8001925C;

extern void func_800181C8();

/* Calls func_800181C8 with the selected 24-byte entry and two forwarded values. */
void func_80016D00(s32 firstValue, s32 unusedValue, s32 secondValue) {
    register s32 entryIndex ASM_REG("$2") = D_80018FB4 % 3;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 twiceEntryIndex ASM_REG("$3") = entryIndex << 1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 thriceEntryIndex ASM_REG("$4") = entryIndex + twiceEntryIndex;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    if (0) {
    }
    func_800181C8(
        (thriceEntryIndex << 3) + (u8 *)&D_80018FB8,
        &D_8001925C,
        firstValue,
        secondValue);
}

/* MECHANISM: The 24-byte outgoing-argument frame saves only $ra; no callee-saved holds.
   -fno-schedule-insns preserves the retail global-load-before-divide-magic order.
   Guarded short roles entryIndex:$v0, twiceEntryIndex:$v1, thriceEntryIndex:$a0 close the scale-tree coloring. */
