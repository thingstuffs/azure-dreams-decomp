#include "common.h"

void func_800A86DC(s32 arg0) {
    u8 *ptr = (u8 *)0x80010000;

    if (arg0 < 19) {
        ptr += arg0 * 4;
        do {
            ASM_KEEP(ptr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            arg0++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        } while (arg0 < 19);
    }
    {
        u8 *page = (u8 *)0x80010000;
        s32 offset;

        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        offset = arg0 * 4;
        *(s32 *)(offset + (u32)page + 0x29C) = 0;
    }
}
