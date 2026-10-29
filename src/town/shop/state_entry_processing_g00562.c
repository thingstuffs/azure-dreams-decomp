/* State entry processing (G00562). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2608, CL:town/func_800A265C, CL:town/func_800A2724. */
#include "town/shop/state_entry_processing_g00562.h"
#include "town/shop.h"

/* Load a record into the shared buffer, process it, and write it back. */
void load_a_shared_buffer_process_write_back(s32 record_ref) {
    restore_actor_stats_from_snapshot(&town_actor_scratch, record_ref);
    reset_person_object_entries(&town_actor_scratch);
    build_entity_slot_snapshot(record_ref, &town_actor_scratch);
}

/* Processes entries in state 19 and triggers their associated sounds. */
void process_entries_in_state_n_19_triggers_associated_sounds(void) {
    s32 entry_count;
    s32 entry_index;
    u8 *entry;
    u8 state;

    entry_count = town_record_capacities[find_target_byte_index_in_list()];
    entry = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        state = entry[0x981 + entry_index * 4];
        if (state != 0) {
            if (state == 19) {
                load_a_shared_buffer_process_write_back((s32)(0x80010A80 + ((entry[0x983 + entry_index * 4] & 0x3F) * 84)));
                set_resident_bitmap_bit(paired_scene_flag_ids[entry_index]);
            }
        }
    }
}

/*
 * Walks the zero-terminated town item pointer table and processes the 84-byte record selected by
 * each type-0x13 object byte-3 low five bits.
 */
void process_table_entries_referenced_objects_type_hex_13(void) {
    void **object_entry;
    u8 *object;
    s32 object_type;
    u32 table_base;

    if (town_item_list != 0) {
        object_type = 0x13;

        table_base = 0x800102F0;

        object_entry = (void **)0x8001029C;
        do {
            object = *object_entry;
            if (object[1] == object_type) {
                load_a_shared_buffer_process_write_back((s32)((object[3] & 0x1F) * 84 + table_base));
            }
            object_entry++;
        } while (*object_entry != 0);
    }
}

/* Calls process_entries_in_state_n_19_triggers_associated_sounds followed by process_table_entries_referenced_objects_type_hex_13. */
void process_state_entries_and_referenced_objects(void) {
    process_entries_in_state_n_19_triggers_associated_sounds();
    process_table_entries_referenced_objects_type_hex_13();
}
