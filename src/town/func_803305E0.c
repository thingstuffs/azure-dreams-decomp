#include "common.h"

extern s8 D_80016000[];

/* Returns the indexed flag mask, with indices 0 and 1 yielding constant false and true. */
s32 func_8001ADE0(s32 flagIndex) {
    s32 wordOffsetOrBitIndex;
    s32 addressOrMask;
    s32 *flagWord;
    s32 result;

    if (flagIndex != 0) {
        if (flagIndex != 1) {
            addressOrMask = *(s32 *)D_80016000;
            wordOffsetOrBitIndex = flagIndex / 32;
            addressOrMask = *(s32 *)(addressOrMask + 0x18);
            flagWord = (s32 *)(wordOffsetOrBitIndex * sizeof(s32) + addressOrMask);
            wordOffsetOrBitIndex = flagIndex % 32;
            addressOrMask = 1;
            addressOrMask <<= wordOffsetOrBitIndex;
            result = addressOrMask & *flagWord;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}
