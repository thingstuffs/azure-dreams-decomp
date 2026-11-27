#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "dungeon/actor/object.h"
#include "town/person/object/initialize_object_entries_api.h"

extern M2C_UNK D_800CB21C;
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to seven. */
void initialize_object_with_seven_tick_counter(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *sprite) {
    initialize_object_entries(object, sprite, D_800D6910);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = &D_800CB21C;
    object->timer = 7;
}
