/* Resource slots (G00521).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008DB84, CL:town/func_8008DBC8, CL:town/func_8008DC4C, PD:town/engine:800CF828, PD:town/engine:800CF838.
 */
#include "town/scene/resource/resource_slots_g00521.h"

/* Returns whether any of the 15 selected entries passes resource_value_table_contains. */
s32 has_listed_resource_in_slots(void) {



    s32 entry_index;

    for (entry_index = 0; entry_index < 15; entry_index++) {
        if (resource_value_table_contains((s32)D_800CF838[D_800CF828[entry_index]]) != 0) {
            return 1;
        }
    }

    return 0;
}

/* Return the slot whose mapped pointer matches D_80080EA8, or -1. */
s32 find_slot_for_resource_entry(void) {


    s32 slot_index;

    for (slot_index = 0; slot_index < 15; slot_index++) {
        if (D_800CF838[D_800CF828[slot_index]] == D_80080EA8) {
            return slot_index;
        }
    }

    return -1;
}

/* reserve_twch_load: reserve a town character load in an available character_slot and process it. */
void reserve_twch_load(s32 character_id) {


    s32 i;
    s32 found;

    found = resource_value_table_contains((s32)((void **)D_800CF838)[character_id]);
    i = 0;
    if (found != 0) {
        i = find_slot_for_resource_entry();
        if (i >= 0) {
            D_800CF828[i] = character_id;
            return;
        }
        i = 0;
    }

    do {
        if (D_800CF828[i] == 0) {
            D_800CF828[i] = character_id;
            D_800CF828[i + 1] = 0;
            return;
        }
        i++;
    } while (i < 15);
}

/* Process the 15 object slots and update the first slot from the status check. */
void func_8008B4B0(void) {


    s32 slot;
    u8 *object_ids;
    void **objects;
    u8 *id_ptr;

    slot = 0;
    object_ids = D_800CF828;
    objects = D_800CF838;
    do {
        id_ptr = (u8 *)((unsigned long)slot + (unsigned long)object_ids);

        if (*id_ptr != 0) {
            file_load_com(objects[*id_ptr]);
        }
        slot++;
    } while (slot < 15);

    if (has_listed_resource_in_slots() != 0) {
        D_800CF828[0] = 1;
        D_800CF828[1] = 0;
        return;
    }
    D_800CF828[0] = 0;
}
