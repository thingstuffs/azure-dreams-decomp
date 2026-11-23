#include "common.h"
#include "shared/game_state.h"
#include "engine/entity.h"

/* Replace state 0x39 with 2 in entries tagged 0x13 and their linked records. */
void reset_tagged_entry_states(void) {
    s32 slot;
    u32 ram_base;
    u32 packed_index;
    s32 match_tag;
    s32 old_state;
    s32 new_state;
    u32 record_index;

    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers. */
    do {
        slot = 0x3F;
    } while (0);
    ram_base = 0x80010000;
    match_tag = 0x13;
    old_state = 0x39;
    new_state = 2;
    for (; slot >= 0; slot--) {
        if (GAME_STATE->town_monster_entries[slot].kind == match_tag && GAME_STATE->town_monster_entries[slot].unk_00 == old_state) {
            packed_index = GAME_STATE->town_monster_entries[slot].unk_03;
            GAME_STATE->town_monster_entries[slot].unk_00 = new_state;
            record_index = packed_index & 0x3F;
            ((u8 *)ram_base)[record_index * 0x54 + 0xA93] = new_state;
        }
    }

    slot = 0x13;
    ram_base = 0x80010000;
    match_tag = slot;
    old_state = 0x39;
    new_state = 2;
    for (slot = slot; slot >= 0; slot--) {
        if (GAME_STATE->items[slot].kind == match_tag && GAME_STATE->items[slot].unk_00 == old_state) {
            GAME_STATE->items[slot].unk_00 = new_state;
        }
        if (GAME_STATE->carry.items[slot].kind == match_tag && GAME_STATE->carry.items[slot].unk_00 == old_state) {
            packed_index = GAME_STATE->carry.items[slot].unk_03;
            GAME_STATE->carry.items[slot].unk_00 = new_state;
            record_index = packed_index & 0x1F;
            ((u8 *)ram_base)[record_index * 0x8C + 0x2273] = new_state;
        }
    }
}
