#include "common.h"

extern u8 *D_800E3D7C;

/* Checks the entity or its two linked objects for the 0x20000000 state flag. */
s32 func_800C7FFC(u8 *entity) {
    s32 slot_index;
    u32 state_mask;
    unsigned long slots_base;
    unsigned long globals_page;
    unsigned long slot;
    u8 *candidate;

    if (*(u32 *)(entity + 0x14) & 0x4000) {
        globals_page = 0x800E0000;
        ASM_KEEP(globals_page);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        slot_index = 1;
        slots_base = (unsigned long)*(u8 **)(globals_page + 0x3D7C);
        state_mask = 0x20000000;
        slot = slots_base + 4;
        while (slot_index >= 0) {
            candidate = *(u8 **)(slot + 0xAC);
            if (candidate != 0 && (*(u32 *)(candidate + 0x54) & state_mask)) {
                return 1;
            }
            slot_index--;
            slot -= 4;
        }
        return 0;
    }

    slot = *(u32 *)(entity + 0x54);
    entity = (u8 *)0x20000000;
    slot &= (u32)entity;
    if (!slot) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        return 0;
    }
    return 1;
}
