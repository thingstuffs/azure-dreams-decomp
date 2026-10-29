#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state.h"
extern u8 D_800CBFAC[];
extern s32 D_800D6A70[];

// Initialize the object, clear its state fields and indexed flag, and set its data pointer.
void initialize_indexed_callback_state(void *object, s32 unused, void *initValue) {
    initialize_object_entries(object, initValue, D_800D6A70);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(s16 *)((u8 *)object + 0x68) = 0;
    *(s16 *)((u8 *)object + 0x6A) = 0;
    *(void **)((u8 *)object + 0x54) = D_800CBFAC;
    *(s16 *)((u8 *)object + 0x6C) = 0;
}
