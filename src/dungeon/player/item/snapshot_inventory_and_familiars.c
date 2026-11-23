#include "shared/actor_status_ids.h"
#include "shared/game_state.h"
#include "common.h"
#include "dungeon/player/item.h"
#include "engine/entity.h"
#include "engine/scene.h"
#include "slus.h"
#include "dungeon/actor/effect.h"

typedef struct {
    u32 word[35];
} Blob140;

extern s32 familiar_record_slots[];
extern u8 familiar_record_storage[];

/* Snapshot records and state fields, converting stored pointers to table indices. */
void snapshot_inventory_and_familiars(void *input_state) {
    void *state;
    s32 slot_index;
    u8 *src_cursor;

    state = input_state;
    build_entity_slot_snapshot(&GAME_STATE->carry.player, state);

    {
        s32 record_index;
        u8 entry_flags;
        u8 *entry_flags_ptr;
        s32 *record_table;
        u8 *record_buffer;
        Blob140 *copy_src;
        Blob140 *copy_dst;
        unsigned long record_offset;
        s32 *record_slot;

        slot_index = 0x13;
        record_table = familiar_record_slots;
        record_buffer = familiar_record_storage;
        entry_flags_ptr = (u8 *)0x8001024B;
        do {
            if (entry_flags_ptr[-2] == 0x13) {
                entry_flags = entry_flags_ptr[0];
                if ((entry_flags & 0x20) != 0) {
                    record_index = entry_flags & 0x1F;
                    src_cursor = (u8 *)record_table[record_index];
                    if ((get_entity_effect_value(src_cursor, STATUS_FROG) << 0x10) != 0) {
                        src_cursor[0x13] = src_cursor[0xA8];
                    }
                    record_offset = record_index * 0x8C;
                    copy_dst = (Blob140 *)(record_offset + (unsigned long)record_buffer);
                    copy_src = (Blob140 *)src_cursor;
                    *copy_dst = *copy_src;
                    record_slot = (s32 *)((record_index << 2) + (unsigned long)record_table);
                    *record_slot = (s32)((record_index * 0x8C) + (unsigned long)record_buffer);
                }
            }
            slot_index -= 1;
            entry_flags_ptr += 4;
        } while (slot_index >= 0);
    }

    {
        GameState *globals;

        globals = GAME_STATE;
        slot_index = 0x13;
        do {
            globals->carry.items[slot_index] = globals->items[slot_index];
            /* get_bounded_stride_index takes the addresses as integers. */
            globals->carry.item_list[slot_index] = get_bounded_stride_index((unsigned long)globals->item_list[slot_index], (unsigned long)GAME_STATE->items, 4, 0x14);
            ((Blob140 *)globals->carry.familiar_records)[slot_index] = ((Blob140 *)familiar_record_storage)[slot_index];
            globals->carry.familiar_slots[slot_index] = get_bounded_stride_index(familiar_record_slots[slot_index], familiar_record_storage, 0x8C, 0x14);
            slot_index -= 1;
        } while (slot_index >= 0);
    }

    {
        u8 *saved_source;
        u8 *index_cursor;

        slot_index = 1;
        index_cursor = (u8 *)0x80010000;
        saved_source = state;
        saved_source += 4;
        do {
            /* get_bounded_stride_index takes the addresses as integers. */
            index_cursor[slot_index + 0x2D52] = get_bounded_stride_index(*(s32 *)(saved_source + 0xD0), (unsigned long)GAME_STATE->items, 4, 0x14);
            saved_source -= 4;
            slot_index -= 1;
        } while (slot_index >= 0);
    }

    {
        GameState *state_base;
        u32 field_value;
        u32 saved_setting;

        state_base = GAME_STATE;
        field_value = state_base->egg_counter;
        saved_setting = state_base->fruit_counter;
        state_base->egg_counter_saved = field_value;
        state_base->fruit_counter_saved = saved_setting;
        field_value = *(u16 *)((u8 *)state + 0xF8);
        state_base->carry.player_F8 = field_value;
        field_value = *(s32 *)((u8 *)state + 0xFC);
        state_base->carry.dungeon_money = field_value;
        field_value = ((u8 *)state)[0xFA];
        state_base->carry_player_FA[0] = field_value;
        field_value = ((u8 *)state)[0xFB];
        state_base->carry_player_FA[1] = field_value;
        snapshot_item_flag_bitmap(saved_setting);
    }
}
