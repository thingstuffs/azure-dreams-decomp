#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80099844(s32, void *);
extern u8 D_800E0600[];

/* Passes a nonzero table entry to func_80099844 when the global state is 1. */
s32 func_80094208(s32 entry_index) {
    s32 entry;

    {
        s32 *table_base = ((s32 *)&D_800E3D7C);

        entry = *(s32 *)((s8 *)(((s32)(entry_index << 0x10) >> 0xE) + *table_base) + 0xAC);
    }
    if (entry != 0) {
        s32 active_state = 1;

        if (*(s32 *)0x80012090 == active_state) {
            func_80099844(entry, D_800E0600);
            return 1;
        }
    }
    return 0;
}
