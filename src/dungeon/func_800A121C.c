#include "common.h"

extern s32 utility_count_word(s32, s32) __asm__("func_800A6928");

/* Returns 1 if the packed byte pair is in the table, otherwise checks func_800A6928. */
s16 func_800A697C(s32 highByte, s32 lowByte) {
    s32 packedBytes = highByte << 8;
    s32 remainingEntries;
    s32 searchKey;
    u16 *entry;

    packedBytes |= lowByte & 0xFF;
    remainingEntries = 0x3F;
    searchKey = packedBytes & 0xFFFF;
    entry = (u16 *)0x8001207C;

    while (1) {
        if (*entry == searchKey)
            return 1;
        if (--remainingEntries < 0)
            break;
        entry -= 2;
    }
    return utility_count_word(highByte & 0xFF, lowByte & 0xFF);
}
