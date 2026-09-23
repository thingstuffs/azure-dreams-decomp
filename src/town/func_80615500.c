#include "common.h"

extern s32 D_80018FB4;
extern s32 D_80018FB8;
extern s32 D_8001925C;

extern void func_800181C8();

/* Calls func_800181C8 with the selected 24-byte entry and two forwarded values. */
void func_80016D00(s32 firstValue, s32 unusedValue, s32 secondValue) {
    s32 entryIndex;
    s32 twiceEntryIndex;
    s32 thriceEntryIndex;
    thriceEntryIndex = D_80018FB4;
    entryIndex = thriceEntryIndex - (thriceEntryIndex / 3) * 3;
    twiceEntryIndex = entryIndex << 1;
    thriceEntryIndex = entryIndex + twiceEntryIndex;

    func_800181C8(
        (thriceEntryIndex << 3) + (u8 *)&D_80018FB8,
        &D_8001925C,
        firstValue,
        secondValue);
}

