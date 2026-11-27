#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "dungeon/actor/object.h"
#include "town/person/object/initialize_object_entries_api.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "shared/object_index_slots.h"
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to six. */
void initialize_object_with_six_tick_counter(struct TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *sprite) {

    initialize_object_entries(object, sprite, D_800D6910);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = &advance_object_countdown_and_invoke_handlers;
    object->timer = 6;
}
