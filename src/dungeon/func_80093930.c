#include "common.h"

extern u8 D_800E3E48[];

/* Return the index of the first unused entry, or -1 if all entries are occupied. */
s32 func_80099090(void)
{
    u8 *entry;
    s32 index;
    s32 result;

    do {
        index = 0;
    } while (0);
    entry = D_800E3E48;
loop:
    if (entry[0x13] == 0) {
        result = index;
        goto done;
    }

    index++;
    entry += 0x8C;
    if (index < 0x14) {
        goto loop;
    }

    result = -1;
done:
    ASM_KEEP(result);
    return result;
}
