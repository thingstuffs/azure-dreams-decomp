#include "common.h"
#include "town/player/motion.h"
#include "town/player/record.h"
#include "town/player.h"

#include "town/player/action_reset_data.h"


/* Initialize the record from source fields, preserve its current value, and clear the global flag. */
void copy_motion_parameters_and_reset_flag(void *record_arg, ObjectPosition *source) {
    TownPlayerRecord *record = record_arg;

    u16 saved_value;
    u16 source_value;

    *(s32 *)((s8 *)record + 0) = (s32)invoke_object_state_callback;
    record->move_target_x = source->x.unsigned_parts.integer;
    saved_value = (u16)record->facing;
    source_value = source->y.unsigned_parts.integer;
    record->saved_facing = saved_value;
    record->move_target_y = source_value;
    town_action_reset_byte[0] = 0;
}
