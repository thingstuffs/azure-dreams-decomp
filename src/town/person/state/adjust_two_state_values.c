#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "engine/object.h"
#include "town/person/object.h"
#include "town/person/state.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */

typedef struct S_800C56A8_0 {
    s32 unk_00;
    s32 unk_04;
} S_800C56A8_0;   /* arg1 in adjust_two_state_values */


/* Adjust the two state values and run completion actions when the countdown expires. */
void adjust_two_state_values(Rec_func_80094268_arg0 *object, S_800C56A8_0 *state) {
    u16 ticks_left;

    state->unk_00 = (s32) (state->unk_00 + 0xFFFEAAAB);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    ticks_left = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        set_resident_bitmap_bit(F_act_yoda);
        unlink_scene_list_node(object);
        clear_object_slot_and_mark_removed(object);
    }
}
