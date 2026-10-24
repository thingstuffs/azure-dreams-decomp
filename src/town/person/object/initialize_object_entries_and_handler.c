#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
extern void create_object_given_position_preset(void *position);
extern u8 D_800C5D38;
extern u8 D_800D5598;

// Sets up an object, clears its indexed flag, assigns its state pointer, and runs the follow-up update.
void initialize_object_entries_and_handler(void *object, void *followupValue, void *setupValue) {
    initialize_object_entries(object, setupValue, &D_800D5598);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(u8 **)((u8 *)object + 0x54) = &D_800C5D38;
    create_object_given_position_preset(followupValue);
}
