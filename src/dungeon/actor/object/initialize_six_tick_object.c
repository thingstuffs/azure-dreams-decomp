#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "dungeon/actor/object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void initialize_object_entries(void *,s8 *, s32 *);
extern u8 object_index_slots[][8];
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to six. */
void initialize_object_with_six_tick_counter(void *object_arg, ObjectPosition *unused, void *context) {
    TownObjectRecord *object = object_arg;

    initialize_object_entries(object, context, D_800D6910);
    object_index_slots[object->slot][0] = 0;
    object->handler = &advance_object_countdown_and_invoke_handlers;
    object->timer.as_s16 = 6;
}
