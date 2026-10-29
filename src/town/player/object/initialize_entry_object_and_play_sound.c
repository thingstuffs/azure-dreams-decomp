#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "slus.h"
#include "town/player/object.h"

typedef struct TownEntry {
    u8 pad0[2];
    s8 table_index;
    u8 pad3[5];
} TownEntry;

typedef struct TownObject {
    u8 pad0[4];
    void *handler;
    u8 pad8[2];
    s16 state;
    u8 padC[4];
    u16 value;
    u8 pad12[0x2E];
    s32 entry_index;
} TownObject;

extern u8 D_800983BC;
extern u8 D_800D0158;
extern u16 town_facing_angles[];

/* Set the object's handler, state, and entry-specific value, then update the table target. */
void initialize_entry_object_and_play_sound(TownObject *object, s32 table_target, void *ptr2) {
    TownEntry *entries;
    u16 entry_value;

    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0158, (Rec_func_80094268_arg0 *) object, ptr2);
    entries = object_index_slots;
    entries[1].pad0[0] = 0;
    entry_value = town_facing_angles[entries[object->entry_index].table_index];
    object->handler = &D_800983BC;
    object->state = 3;
    object->value = entry_value;
    clear_entity_record_fields(table_target);
    SD_Call(0x519);
}
