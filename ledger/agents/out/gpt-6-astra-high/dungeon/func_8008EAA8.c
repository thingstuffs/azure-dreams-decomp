#include "common.h"

extern void func_80099844(s32, void *);
extern s32 D_80012090[];
extern u8 D_800E0600[];
extern s32 D_800E3D7C;

/* Passes a nonzero table entry to func_80099844 when the global state is 1. */
s32 func_80094208(s32 entry_index) {
    s32 entry;

    {
        s32 *table_base = &D_800E3D7C;

        entry = *(s32 *)((s8 *)(((s32)(entry_index << 0x10) >> 0xE) + *table_base) + 0xAC);
    }
    if (entry != 0) {
        s32 active_state = 1;

        ASM_KEEP(active_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (D_80012090[0] == active_state) {
            func_80099844(entry, D_800E0600);
            return 1;
        }
    }
    return 0;
}
