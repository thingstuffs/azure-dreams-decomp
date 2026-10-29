/* Release handled entries and change the monster status target (G00635). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B93B0, CL:town/func_800B97F4. */
#include "town/shop/monster_status_target_updates_g00635.h"
#include "shared/object_flags.h"
#include "town/shop.h"

/* Processes 24 entries by type and clears the handle and type of handled entries. */
void process_handled_entry_types(void **entries) {
    s32 entry_index;
    u8 entry_type;
    S_800B6B10_0 *entry;

    for (entry_index = 0; entry_index < 0x18; entry_index++) {
        entry = entries[entry_index];
        entry_type = ((S_800B6B10_4 *)(((S_800B6B10_2 *)entry)->unk_04))->unk_0E;
        if (entry_type == 2) {
            flag_optional_object_for_removal(entry->unk_00);
            ((S_800B6B10_1 *)entries[entry_index])->unk_00 = 0;
            ((S_800B6B10_5 *)(((S_800B6B10_3 *)entries[entry_index])->unk_04))->unk_0E = 0;
        } else if (entry_type == 1) {
            flag_object_for_removal(entry->unk_00);
            ((S_800B6B10_1 *)entries[entry_index])->unk_00 = 0;
            ((S_800B6B10_5 *)(((S_800B6B10_3 *)entries[entry_index])->unk_04))->unk_0E = 0;
        }
    }

}

/* Process an object's pointer array and embedded state, then set its and the global 0x8000 flags. */
void process_object_pointer_array(S_800B9464_a0 *object)
{
    S_800B9464_sub *objectState;

    if (object != 0) {
        objectState = &object->sub;
        release_null_terminated_entries(object->arr_bc);
        process_handled_entry_types((void **)objectState->unk98);
        release_monster_status_request_handles(objectState);
        object->field_1E |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

/* Updates the embedded object state and runs its associated helpers. */
void change_monster_status_display_target(s32 objectAddress, s32 field04Value, s16 field08Value) {
    S_800B6C30_0 *objectState;

    if (objectAddress != 0) {
        objectState = objectAddress + 0x20;
        process_handled_entry_types((void * *)(objectState->unk_98));
        objectState->unk_08 = field08Value;
        objectState->unk_04 = field04Value;
        process_object_data_by_mode(objectState);
        invalidate_cached_state_and_queue_read(objectState);
    }
}
