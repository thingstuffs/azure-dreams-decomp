#include "common.h"

extern void *D_80010248[];
extern u8 D_80081484[];
extern u8 *D_800E3D7C;

/* Selects a table entry address, fixed buffer, or current data pointer by ID. */
u8 *func_8009FADC(s32 selector_id) {
    s16 selector_index = selector_id - 1;
    u8 *result;
    if (selector_index < 0x14) {
        result = (u8 *)(0x80010248 + (selector_index * (s32)sizeof(void *)));
    } else if (selector_index != 0x14) {
        result = *(u8 **)(D_800E3D7C + 0xF0);
    } else {
        result = D_80081484;
    }
    ASM_SCHED_BARRIER();   /* MATCH: Keep both selector arms jumping to the shared return. */
    return result;
}

/* MECHANISM: Frameless s16 selector preserves the retail a0 lifetime and CFG.
   Pinned v0 results plus the noreturn callee reproduce both continuation tails.
   Raw table addressing and the final fence place both page loads in retail slots. */
