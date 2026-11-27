#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"
#include "town/data.h"
#include "shared/object_index_slots.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} D_80082660_entry;

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern M2C_UNK person_bounce_handler_address;

/* Initializes the object from its table entry and resets the companion state. */
void initialize_bounce_reaction_object(TownObjectRecord *object, ObjectPosition *state, SpriteFrameState *sprite) {
    s8 entry_value;

    initialize_object_entries((object), sprite, person_reaction_object_entries);
    object_index_slots[5].motion_id = 0;
    entry_value = (s8)object_index_slots[object->slot].motion_param;
    object->handler = &person_bounce_handler_address;
    object->unk_90 = (s16) entry_value;
    state->velocity_z = 0xFFF60000;
}
