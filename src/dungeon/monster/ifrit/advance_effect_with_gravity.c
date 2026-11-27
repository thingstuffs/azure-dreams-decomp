#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad0[8];
    s32 pinch_offset;
    s32 profile_peak;
    s32 profile_velocity;
    s32 profile_accel;
    u16 remaining_ticks;
} Func80A209A4Data;


/* Advance motion and set completion flags when the countdown expires. */
void advance_effect_with_gravity(Func80A209A4Data *motion) {
    Func80A209A4Data *data = motion;
    u16 ticks_left;

    data->profile_peak += data->profile_velocity;
    data->profile_velocity += data->profile_accel;
    data->profile_accel += 0xFFFF4000;
    data->pinch_offset += 0x10000;
    ticks_left = data->remaining_ticks - 1;
    data->remaining_ticks = ticks_left;
    if ((ticks_left << 16) <= 0) {
        *(u16 *)((u8 *)data - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
