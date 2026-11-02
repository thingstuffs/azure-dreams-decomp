#include "common.h"
#include "town/person/state_updates.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"
extern s32 D_800D54DC[];
extern u8 D_800D55E8[];
extern u8 D_800D55F0[];
extern u8 D_800D5618[];
extern u8 D_800D561C[];

/* Initialize the object tables and clear its indexed status byte. */
void initialize_object_tables(TownObjectRecord *object, s32 unused, void *init_value) {
    object_index_slots[object->slot].unk_00 = 0;
    *(void **)((u8 *)object + 0x58) = D_800D5618;
    *(void **)((u8 *)object + 0x5C) = D_800D561C;
    object->unk_7C.as_pv = D_800D55E8;
    *(void **)((u8 *)object + 0x80) = D_800D55F0;
    initialize_object_entries(object, init_value, D_800D54DC);
    object->handler = person_table_handler_address;
}
