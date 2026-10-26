/* Resource value table contains g01112.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01112 - CL:town/func_8008DB84, CL:town/func_8008DBC8, CL:town/func_8008DC4C, PD:town/engine:800CF828, PD:town/engine:800CF838.
 */
#include "town/scene/resource/resource_value_table_contains_g01112.h"

/* Return whether the zero-terminated table contains the target value. */
s32 resource_value_table_contains(void *target_value) {
    s32 i = 0;

    while (town_resource_ids[i] != 0) {
        if (target_value == town_resource_ids[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

/* Returns whether any of the 15 selected entries passes resource_value_table_contains. */
s32 has_listed_resource_in_slots(void) {



    s32 entry_index;

    for (entry_index = 0; entry_index < 15; entry_index++) {
        if (resource_value_table_contains(town_resource_descriptors[town_resource_queue[entry_index]]) != 0) {
            return 1;
        }
    }

    return 0;
}

/* Return the slot whose mapped pointer matches D_80080EA8, or -1. */
s32 find_slot_for_resource_entry(void) {


    s32 slot_index;

    for (slot_index = 0; slot_index < 15; slot_index++) {
        if (town_resource_descriptors[town_resource_queue[slot_index]] == D_80080EA8) {
            return slot_index;
        }
    }

    return -1;
}

/* reserve_twch_load: reserve a town character load in an available character_slot and process it. */
void reserve_twch_load(s32 character_id) {


    s32 i;
    s32 found;

    found = resource_value_table_contains(town_resource_descriptors[character_id]);
    i = 0;
    if (found != 0) {
        i = find_slot_for_resource_entry();
        if (i >= 0) {
            town_resource_queue[i] = character_id;
            return;
        }
        i = 0;
    }

    do {
        if (town_resource_queue[i] == 0) {
            town_resource_queue[i] = character_id;
            town_resource_queue[i + 1] = 0;
            return;
        }
        i++;
    } while (i < 15);
}

/* Process the 15 object slots and update the first slot from the status check. */
void load_reserved_slot_resources(void) {


    s32 slot;
    u8 *object_ids;
    void **objects;
    u8 *id_ptr;

    slot = 0;
    object_ids = town_resource_queue;
    objects = town_resource_descriptors;
    do {
        id_ptr = (u8 *)((unsigned long)slot + (unsigned long)object_ids);

        if (*id_ptr != 0) {
            file_load_com(objects[*id_ptr]);
        }
        slot++;
    } while (slot < 15);

    if (has_listed_resource_in_slots() != 0) {
        town_resource_queue[0] = 1;
        town_resource_queue[1] = 0;
        return;
    }
    town_resource_queue[0] = 0;
}
