#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3A98;
#include "town/person/object/initialize_object_entries_api.h"

// Updates an object using its linked data, then resets its indexed flag and state.
void reset_object_handler_after_update(void *object, s32 unused, void *updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    initialize_object_entries(object, updateValue, *(s32 **)((u8 *)objectData + 8));
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &D_800C3A98;
    *(s16 *)((u8 *)object + 0x6C) = 0x20;
}
