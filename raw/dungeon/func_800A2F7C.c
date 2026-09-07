#include "common.h"

void func_800A86DC(s32 arg0) {
    u8 *ptr = (u8 *)0x80010000;

    if (arg0 < 19) {
        ptr += arg0 * 4;
        do {
            ASM_KEEP(ptr);
            arg0++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        } while (arg0 < 19);
    }
    {
        register u8 *page ASM_REG("$3") = (u8 *)0x80010000;
        register s32 offset ASM_REG("$2");

        ASM_KEEP(page);
        offset = arg0 * 4;
        ASM_KEEP(offset);
        *(s32 *)(offset + (u32)page + 0x29C) = 0;
    }
}
