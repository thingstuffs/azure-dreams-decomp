#include "common.h"

extern s8 D_80016000[];

/* Returns the indexed flag mask, with indices 0 and 1 yielding constant false and true. */
s32 func_8001ADE0(s32 flagIndex) {
    register s32 wordOffsetOrBitIndex ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 addressOrMask ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
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
            ASM_KEEP(flagWord);   /* MATCH pin: keeps a statement from moving across a call/branch */
            result = addressOrMask & *flagWord;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}
