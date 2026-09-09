#include "common.h"

extern u8 *D_800E3D7C[];
extern u16 D_80013716;

s32 func_8009F5CC(void) {
    u8 *page = (u8 *)0x800E0000;
    s32 flags = *(s32 *)(page + 0x296C);
    s32 result;

    if (flags & 0x10000000) {
        result = 0;
        goto done;
    }

    if (*(u16 *)(D_800E3D7C[0] + 0x118) < 0x401) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (D_80013716 < 0xC01) {
            result = 0;
            goto done;
        }
    }

    if (!(flags & 0x400000)) {
        *(s32 *)(page + 0x296C) = flags | 0x400000;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        result = 1;
    } else {
        ASM_SCHED_BARRIER(); /* MATCH: keep zero in the failure arm. */
        result = 0;
    }
done:
    ASM_SCHED_BARRIER(); /* MATCH: keep the arms joined at the shared return. */
    return result;
}
