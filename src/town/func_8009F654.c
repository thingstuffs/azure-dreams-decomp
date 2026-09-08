#include "common.h"

extern s32 *D_801007F4;
extern s32 D_80100900[];

/* Initializes the shared data pointer and clears its first word. */
void func_8009CDB4(void) {
    register s32 *page_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    *(volatile s32 **)&D_801007F4 = (({
#ifdef NON_MATCHING
        page_base = D_80100900 - 0x240;
#else
        page_base = (s32 *)0x80100000;
        ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif
        page_base;
    }) + 0x240);
    page_base[0x240] = 0;
}
