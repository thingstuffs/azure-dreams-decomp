#include "common.h"

extern u8 D_800E3E48[];

s32 func_80099090(void)
{
    u8 *entry;
    register s32 index ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 result ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

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
    ASM_KEEP(result);   /* MATCH pin: retail basic-block layout depends on it */
    return result;
}
