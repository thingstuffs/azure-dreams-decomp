#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
extern u8 D_800CB0F0[];
extern u8 D_800D68D4[];

/* Initializes an entity, sets its state to 6, and copies its table entry's byte. */
void initialize_entity_action_state(void *entity, s32 unused, void *init_value) {
    initialize_object_entries(entity, init_value, D_800D68D4);
    (*(u8 *)&object_index_slots[*(s32 *)((u8 *)entity + 0x60)].unk_00) = 0;
    *(void **)((u8 *)entity + 0x54) = D_800CB0F0;
    *(s16 *)((u8 *)entity + 0x6C) = 6;
    *(u8 *)((u8 *)entity + 0x96) = object_index_slots[*(s32 *)((u8 *)entity + 0x60)].unk_02;
}
