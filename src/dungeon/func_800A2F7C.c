#include "common.h"

void func_800A86DC(s32 arg0) {
    u8 *ptr = (u8 *)0x80010000;

    if (arg0 < 19) {
        ptr += arg0 * 4;
        do {
            ASM_KEEP(ptr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            arg0++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        } while (arg0 < 19);
    }
    {
        u8 *page = (u8 *)0x80010000;
        s32 offset;

        ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        offset = arg0 * 4;
        *(s32 *)(offset + (u32)page + 0x29C) = 0;
    }
}
