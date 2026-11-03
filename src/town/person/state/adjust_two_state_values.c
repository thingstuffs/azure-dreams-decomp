#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "engine/object.h"
#include "town/person/object.h"
#include "town/person/state.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

   /* arg1 in adjust_two_state_values */

/* Adjust the two state values and run completion actions when the countdown expires. */
void adjust_two_state_values(TownObjectRecord *object, ObjectPosition *state) {
    u16 ticks_left;

    state->x.v = (s32) (state->x.v + 0xFFFEAAAB);
    state->y.v = (s32) (state->y.v + 0x40000);
    ticks_left = object->timer.as_u16 - 1;
    object->timer.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        set_resident_bitmap_bit(F_act_yoda);
        unlink_scene_list_node(object);
        clear_object_slot_and_mark_removed(object);
    }
}
