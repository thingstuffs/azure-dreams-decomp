#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk800A5C88;

extern s32 func_800A3450(s32 *, s32);

// Checks up to 12 indices against adjusted input, stopping at the first zero result.
void func_800A33E8(Unk800A5C88 *input) {
    Unk800A5C88 adjustedInput;
    s32 checkIndex;

    adjustedInput.unk0 = input->unk0;
    checkIndex = 0;
    adjustedInput.unk4 = input->unk4;
    adjustedInput.unk8 = input->unk8 - 0x240000;

    do {
        if (func_800A3450(&adjustedInput.unk0, checkIndex) == 0) {
            break;
        }
        checkIndex++;
    } while (checkIndex < 12);
}
