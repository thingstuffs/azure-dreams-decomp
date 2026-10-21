/* Target action dispatch (G00342). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800DF258. */
#include "dungeon/level/target_action_dispatch_g00342.h"

/* Selects and initializes an entry at the given position, returning its slot. */
s32 select_and_initialize_entry_at_position(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value) {
    s32 slot;
    s32 slot_sign;
    s32 entry_type;
    D_800E3648_entry *entries;
    D_800E3648_entry *entry;

    entry_type = type_id;
    slot = find_entry_at_tile_coordinates(x, y, z);
    slot_sign = slot << 0x10;
    if (slot_sign < 0) {
        slot = find_first_free_map_entry();
        slot_sign = slot << 0x10;
        if (slot_sign < 0) {
            slot = 0x1F;
        }
    }
    slot = slot << 0x10;
    slot = slot >> 0x10;
    clear_slot_and_detach_entity(slot);
    entries = (D_800E3648_entry *)floor_objects;
    entry = &entries[slot];
    entry->field1 = 0x15;
    entry->field3 = 0xC0;
    entry->field0 = entry_type;
    entry->field2 = 0;
    dungeon_floor_object_positions[slot].field6 = (s8) x;
    dungeon_floor_object_positions[slot].field7 = (s8) y;
    cycle_map_cell_flags(x, y, 0x20);
    dungeon_floor_object_positions[slot].field10 = z;
    dungeon_floor_object_positions[slot].field14 = 0;
    dungeon_floor_object_positions[slot].fieldC = entry_value;
    dungeon_floor_object_positions[slot].field8 = *(s32 *)(((s32) (entry_type << 0x10) >> 0xE) + (u8 *)D_800DF258);
    return slot;
}

/* Process the target with parameters 7 and 0x10 and report success. */
s32 process_target_with_action_seven(s32 target) {
    set_or_clear_actor_status_slot(target, 7, 0x10);
    return 1;
}

/* Handle a nonzero type 2 query result and always return success. */
s32 handle_type_two_query_result(void *object) {
    if ((get_entity_effect_value(object, 2) << 16) != 0) {
        clear_slots_of_type(object, 2);
        adjust_source_value_and_finalize(object, D_800E0DF5);
        return 1;
    }
    return 1;
}

/* Calls the selected handler and updates object and slot status on success. */
s32 call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state) {
    u8 *state = D_800E3D40;
    s32 result;
    StatusEntry *status;
    Arg1Struct *object = (Arg1Struct *) object_ptr;
    u8 *slot_base;
    s16 slot_index = slot_id;

    state[0] = update_state;
    result = D_800DF2A8[(s16) handler_id](object, slot_index, slot_id << 0x10);
    if (result != 0) {
        if (state[0] != 0) {
            process_unflagged_linked_entries_alt(object->unk5C);
            process_unflagged_linked_entries(object->unk5C);
            g_dungeon_status.flags |= 0x812;
        }
        slot_base = (u8 *) dungeon_floor_object_positions;
        status = (StatusEntry *) (slot_base + slot_index * 0x18);
        if (status->flags & 0x40) {
            func_8003DB94(status, D_800DF258[floor_objects[slot_index * 4]], 0);
            status->flags &= 0xF7FF;
        }
    }
    return result;
}
