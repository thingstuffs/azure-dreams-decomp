#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "dungeon/actor/object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 initialize_object_entries(void *,s8 *, s32 *);          /* extern */
extern M2C_UNK D_800CB21C;
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to seven. */
void initialize_object_with_seven_tick_counter(TownObjectRecord *object, s32 unused, void *context) {
    initialize_object_entries(object, context, D_800D6910);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &D_800CB21C;
    object->timer.as_s16 = 7;
}
