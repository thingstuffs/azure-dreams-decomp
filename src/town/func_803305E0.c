#include "common.h"

extern s8 D_80016000[];

/* Returns the indexed flag mask, with indices 0 and 1 yielding constant false and true. */
s32 func_8001ADE0(s32 flagIndex) {
    register s32 wordOffsetOrBitIndex ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 addressOrMask ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 *flagWord;
    s32 result;

    if (flagIndex != 0) {
        if (flagIndex != 1) {
            addressOrMask = *(s32 *)D_80016000;
            wordOffsetOrBitIndex = flagIndex;
            if (flagIndex < 0) {
                wordOffsetOrBitIndex = flagIndex + 31;
            }
            wordOffsetOrBitIndex >>= 5;
            addressOrMask = *(s32 *)(addressOrMask + 0x18);
            wordOffsetOrBitIndex <<= 2;
            flagWord = (s32 *)(wordOffsetOrBitIndex + addressOrMask);

            wordOffsetOrBitIndex = flagIndex;
            if (flagIndex < 0) {
                wordOffsetOrBitIndex = flagIndex + 31;
            }
            wordOffsetOrBitIndex >>= 5;
            wordOffsetOrBitIndex <<= 5;
            wordOffsetOrBitIndex = flagIndex - wordOffsetOrBitIndex;
            addressOrMask = 1;
            addressOrMask <<= wordOffsetOrBitIndex;
            ASM_KEEP(flagWord);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            result = addressOrMask & *flagWord;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}
