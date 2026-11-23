#include "common.h"
#include "shared/game_state.h"
#include "dungeon/effect/sprite.h"

/* Clears matching table entries and the associated byte in each indexed record. */
void clear_matching_special_item_markers(void) {
    s32 slot_index;
    u32 table_base;
    s32 match_byte1;
    s32 match_byte0;
    u32 *entry;
    u32 record_index;

    slot_index = 0x3F;
    table_base = 0x80010000;
    match_byte1 = 0x13;
    match_byte0 = 2;
    entry = (u32 *)(table_base | 0xA7C);
    do {
        if (GAME_STATE->town_monster_entries[slot_index].kind == match_byte1 && GAME_STATE->town_monster_entries[slot_index].unk_00 == match_byte0) {
            record_index = GAME_STATE->town_monster_entries[slot_index].unk_03 & 0x3F;
            ((u8 *)table_base)[record_index * 0x54 + 0xA93] = 0;
            *entry = 0;
        }
        entry--;
        slot_index--;
    } while (slot_index >= 0);
}
