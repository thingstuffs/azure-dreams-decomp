#include "town/data.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"

/* Check the row flag only while the scene gate is clear. */
s32 check_record_flag_if_unblocked(const Rec_func_800165F4_arg0 *record)
{
    /* BYTES: The result stays in a saved register across the gate test. */
    s32 flag_set = 0;

    if (get_script_flag_mask(scene_gate_script_flag) == 0) {
        flag_set = get_script_flag_mask(record->unk_18) != 0;
    }
    return flag_set;
}
