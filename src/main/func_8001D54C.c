#include "common.h"

void func_8001D54C(void *arg0) {
    s32 i;
    u8 *ptr;
    s32 *out;

    ptr = arg0;
    i = 0;
    do {
        out = *(s32 **)(ptr + 0x1D8);
        ASM_KEEP(out);   /* MATCH pin: keeps a statement from moving across a call/branch */
        *out = 0;
        i++;
        ptr += 4;
    } while (i < 10);
}
