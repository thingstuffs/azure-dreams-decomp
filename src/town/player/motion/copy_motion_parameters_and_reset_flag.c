#include "common.h"
#include "town/player/motion.h"
#include "town/player/record.h"
#include "town/player.h"

extern s8 town_action_reset_byte[9];


/* Initialize the record from source fields, preserve its current value, and clear the global flag. */
void copy_motion_parameters_and_reset_flag(void *record_arg, ObjectPosition *source) {
    TownPlayerRecord *record = record_arg;

    u16 saved_value;
    u16 source_value;

    *(s32 *)((s8 *)record + 0) = (s32)invoke_object_state_callback;
    record->unk_30 = source->x.unsigned_parts.integer;
    saved_value = record->unk_10.as_u16;
    source_value = source->y.unsigned_parts.integer;
    record->unk_0E = saved_value;
    record->unk_32 = source_value;
    town_action_reset_byte[0] = 0;
}
