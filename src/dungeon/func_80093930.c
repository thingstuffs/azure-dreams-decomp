#include "common.h"

extern u8 D_800E3E48[];

s32 func_80099090(void)
{
    u8 *entry;
    register s32 index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    index = 0;
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
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return result;
}
