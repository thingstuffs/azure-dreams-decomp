#include "common.h"

extern s8 D_80016000[];

/* Returns the indexed flag's bit mask, with indices 0 and 1 returning themselves. */
s32 func_80016D78(s32 flagIndex)
{
    s32 wordIndex;
    s32 result;
    s32 *flagState;
    s32 *flagWords;
    s32 flagWord;

    if (flagIndex == 0) {
        goto zero;
    }
    if (flagIndex == 1) {
        goto one;
    }

    flagState = *(s32 **)D_80016000;
    wordIndex = flagIndex / 32;
    flagWords = *(s32 **)((s8 *)flagState + 0x18);
    flagWord = flagWords[wordIndex];
    result = 1 << (flagIndex - wordIndex * 32);
    result &= flagWord;
    goto done;

one:
    result = 1;
    goto done;

zero:
    result = 0;

done:
    return result;
}
