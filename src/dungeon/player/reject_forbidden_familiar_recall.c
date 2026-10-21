#include "common.h"
#include "shared/record_ptrs.h"

extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E0600[];

/* Passes a nonzero table entry to adjust_source_value_and_finalize when the global state is 1. */
s32 reject_forbidden_familiar_recall(s32 entry_index) {
    s32 entry;

    {
        s32 *table_base = ((s32 *)&dungeon_actor_ring_anchor);

        entry = *(s32 *)((s8 *)(((s32)(entry_index << 0x10) >> 0xE) + *table_base) + 0xAC);
    }
    if (entry != 0) {
        s32 active_state = 1;

        if (*(s32 *)0x80012090 == active_state) {
            adjust_source_value_and_finalize(entry, D_800E0600);
            return 1;
        }
    }
    return 0;
}
