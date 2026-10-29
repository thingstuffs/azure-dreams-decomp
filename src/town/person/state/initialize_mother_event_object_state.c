#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state.h"
extern u8 D_800C81E4[];
extern s32 D_800D6110[];

// Initializes the object with D_800D6110, clears its status, and sets state 0x62.
void initialize_mother_event_object_state(void *object, s32 unused, void *initializationArg) {
    *(s32 *)((u8 *)object + 0xA0) = 0;
    initialize_object_entries(object, initializationArg, D_800D6110);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = D_800C81E4;
    *(s16 *)((u8 *)object + 0x6C) = 0x62;
}
