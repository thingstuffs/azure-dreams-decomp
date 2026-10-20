#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void set_resident_bitmap_bit(s32);                     /* extern */
#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */
void clear_object_slot_and_mark_removed(void *);                      /* extern */

typedef struct S_800CA458_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA458_0;   /* arg1 in advance_reaction_state_and_cleanup */


/* Adjust the state values and trigger completion when the object's countdown expires. */
void advance_reaction_state_and_cleanup(Rec_func_80094268_arg0 *object, S_800CA458_0 *state) {
    u16 remainingTicks;

    state->unk_00 = (s32) (state->unk_00 - 0x3333);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    remainingTicks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        set_resident_bitmap_bit(F_act_niko);
        unlink_scene_list_node(object);
        clear_object_slot_and_mark_removed(object);
    }
}
