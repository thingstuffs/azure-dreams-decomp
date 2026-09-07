#include "common.h"

void func_80027B6C(s32 arg0, s32 arg1, s32 arg2) {
    s32 quotient;
    s32 count;
    s32 numerator;
    s32 offset;
    void **entry;
    void *object;

    count = 6;
    numerator = arg1 * 0x90;
    offset = -0x90;
    entry = (void **)(arg0 + 0x18);
    do {
        quotient = numerator / arg2;
        object = *entry++;
        count++;
        *(s16 *)((u8 *)*(void **)((u8 *)object + 4) + 0xA) =
            quotient + offset + 0x90;
        offset += 0x10;
    } while (count < 0xE);
}
