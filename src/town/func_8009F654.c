#include "common.h"

extern s32 *D_801007F4;
extern s32 D_80100900[];

void func_8009CDB4(void) {
    register s32 *base ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *ptr;

    *(volatile s32 **)&D_801007F4 = (ptr = ({
#ifdef NON_MATCHING
        base = D_80100900 - 0x240;
#else
        base = (s32 *)0x80100000;
        ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif
        base;
    }) + 0x240);
    base[0x240] = 0;
}
