#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state.h"
extern u8 D_800CBFAC[];
extern s32 D_800D6A70[];

// Initialize the object, clear its state fields and indexed flag, and set its data pointer.
void initialize_indexed_callback_state(TownObjectRecord *object, s32 unused, void *initValue) {
    initialize_object_entries(object, initValue, D_800D6A70);
    object_index_slots[object->slot].unk_00 = 0;
    object->unk_68 = 0;
    object->unk_6A = 0;
    object->handler = D_800CBFAC;
    object->timer = 0;
}
