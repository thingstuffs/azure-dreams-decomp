#include "town/person.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/object_index_slots.h"
#include "town/person/state.h"

extern s32 D_800C5FDC[];
extern s32 D_800D5590[];

/* Clear the table flag, update the target move, and install D_800C5FDC. */
void install_update_after_flag_clear(PersonObject *object, ObjectPosition *position, SpriteFrameState *output) {
    void *updateObject;
    SpriteFrameState *stagedUpdateValue;

    object_index_slots[object->slot].unk_00 = 0;
    start_person_target_move(object, position, output);
    updateObject = object;
    stagedUpdateValue = output;
    initialize_object_entries(updateObject, stagedUpdateValue, D_800D5590);
    object->handler = D_800C5FDC;
}
