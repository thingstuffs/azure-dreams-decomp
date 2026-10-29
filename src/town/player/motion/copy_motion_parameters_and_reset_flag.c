#include "common.h"
#include "town/player/motion.h"

extern s8 town_action_reset_byte[9];
extern s32 town_position_callback_address[3];

/* Initialize the record from source fields, preserve its current value, and clear the global flag. */
void copy_motion_parameters_and_reset_flag(void *record, void *source) {
    u16 saved_value;
    u16 source_value;

    *(s32 *)((s8 *)record + 0) = (s32)&town_position_callback_address[0];
    *(u16 *)((s8 *)record + 0x30) = *(u16 *)((s8 *)source + 2);
    saved_value = *(u16 *)((s8 *)record + 0x10);
    source_value = *(u16 *)((s8 *)source + 6);
    *(u16 *)((s8 *)record + 0x0e) = saved_value;
    *(u16 *)((s8 *)record + 0x32) = source_value;
    town_action_reset_byte[0] = 0;
}
