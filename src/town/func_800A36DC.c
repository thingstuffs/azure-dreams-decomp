#include "modules/town_door.h"

/* Update the countdown and reset the object's state when it expires. */
void tick_door_countdown(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b) {
    u16 remaining_count;

    decrease_value_and_advance_counter(&D_80100B70, update_arg_a, update_arg_b);
    remaining_count = object->unk_6C - 1;
    object->unk_6C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        change_door_map(object, source->unk_48);
        object->unk_50 = &door_no_op;
        into_dn_door_jobs();
    }
}
