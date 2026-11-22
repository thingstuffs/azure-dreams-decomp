#include "common.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"
extern s32 D_800D6AA8[];

/* Initializes object entries from D_800D6AA8 and increments the state halfword at offset 0x68. */
void load_entries_and_advance_state(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *sprite) {
    initialize_object_entries(object, sprite, D_800D6AA8);
    object->unk_68 += 1;
}
