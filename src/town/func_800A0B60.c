#include "town/menu/window.h"

/* Initializes the shared state from the selected table entry and stores the result. */
s32 initialize_shared_state_from_table(void) {
    u8 *record_table = (u8 *)0x80010A80;
    u32 record_index = D_800CFCC4->unk_4F & 0x3F;
    s32 *state = &D_80100A10;

    restore_actor_stats_from_snapshot(state, record_table + (record_index * 0x54));
    D_80100AF4 = load_and_open_monster_status_display(state, 1, 0x5C, -0x68, 0x200);
    return 0;
}
