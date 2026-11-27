#include "common.h"
#include "shared/game_state.h"
#include "shared/record_ptrs.h"
#include "dungeon/player.h"
#include "dungeon/item.h"
extern u8 dungeon_familiar_recall_floor_forbidden_tail_message[];

/* Passes a nonzero table entry to adjust_source_value_and_finalize when the global state is 1. */
s32 reject_forbidden_familiar_recall(s32 entry_index) {
    void *entry;

    {
        s32 *table_base = ((s32 *)&dungeon_actor_ring_anchor);

        entry = *(void **)((s8 *)(((s32)(entry_index << 0x10) >> 0xE) + *table_base) + 0xAC);
    }
    if (entry != 0) {
        s32 active_state = 1;

        if (GAME_STATE->dungeon_mode_state == active_state) {
            adjust_source_value_and_finalize(entry, dungeon_familiar_recall_floor_forbidden_tail_message);
            return 1;
        }
    }
    return 0;
}
