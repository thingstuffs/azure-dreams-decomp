#include "common.h"

extern u8 *D_800E3D7C[];
extern u16 D_80013716;

/* Sets flag 0x400000 once when the blocking flag is clear and either threshold is met. */
s32 func_8009F5CC(void) {
    u8 *flag_page = (u8 *)0x800E0000;
    s32 flags = *(s32 *)(flag_page + 0x296C);
    s32 changed;

    if (flags & 0x10000000) {
        changed = 0;
        goto done;
    }

    if (*(u16 *)(D_800E3D7C[0] + 0x118) < 0x401) {
        ASM_SCHED_BARRIER();
        if (D_80013716 < 0xC01) {
            changed = 0;
            goto done;
        }
    }

    if (!(flags & 0x400000)) {
        *(s32 *)(flag_page + 0x296C) = flags | 0x400000;
        changed = 1;
    } else {
        changed = 0;
    }
done:
    ASM_SCHED_BARRIER();
    return changed;
}
