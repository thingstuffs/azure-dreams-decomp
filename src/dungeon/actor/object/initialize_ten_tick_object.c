#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

#include "shared/town_object.h"
#include "dungeon/actor/object.h"

#include "town/person/object/initialize_object_entries_api.h"
void func_800CB570(TownObjectRecord *record, s32 forward_arg1, s32 forward_arg2);
extern s32 D_800D694C[];

/* Initialize the object's state, clear its slot flag, and set its counter to ten. */
void initialize_object_with_ten_tick_counter(struct TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *sprite) {

    initialize_object_entries(object, sprite, D_800D694C);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = &func_800CB570;
    object->timer = 0xA;
}
