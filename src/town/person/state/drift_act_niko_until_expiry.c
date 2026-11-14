#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "engine/object.h"
#include "town/person/object.h"
#include "town/person/state.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

typedef struct S_800CA458_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA458_0;   /* arg1 in drift_act_niko_until_expiry */


/* Adjust the state values and trigger completion when the object's countdown expires. */
void drift_act_niko_until_expiry(TownObjectRecord *object, S_800CA458_0 *state) {
    u16 remainingTicks;

    state->unk_00 = (s32) (state->unk_00 - 0x3333);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    remainingTicks = object->timer - 1;
    object->timer = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        set_resident_bitmap_bit(F_act_niko);
        unlink_scene_list_node(object);
        clear_object_slot_and_mark_removed(object);
    }
}
