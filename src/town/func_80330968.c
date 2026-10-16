#include "common.h"

extern void townSetScriptFlagBit(s32);
extern void townClearScriptFlagBit(s32);

/* Dispatches consecutive indices to one of two handlers according to successive mask bits. */
void townWriteScriptFlagRange(s32 base, s32 bits, s32 count)
{
    s32 offset;

    for (offset = 0; offset < count; offset++) {
        if (bits & 1) {
            townSetScriptFlagBit(base + offset);
        } else {
            townClearScriptFlagBit(base + offset);
        }
        bits >>= 1;
    }
}
