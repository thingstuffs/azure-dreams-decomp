#include "common.h"

/* Scales a pitch by a fractional note offset, interpolating between adjacent steps. */
u32 func_8005F740(s32 pitch, u32 note_offset)
{
    s32 frame_pad[2];
    s32 step;
    s32 pitch_low;
    s32 pitch_high;
    u32 whole_steps;
    u32 pitch_scale;

    pitch_scale = 0x103B;
    pitch_low = (u32)pitch << 12;
    step = 0;
    whole_steps = note_offset >> 5;
    note_offset &= 0x1F;
    pitch_high = pitch * pitch_scale;
    if (whole_steps != 0) {
        do {
            pitch_low = pitch * pitch_scale;
            pitch_scale *= 0x103B;
            pitch_scale >>= 12;
            step++;
            pitch_high = pitch * pitch_scale;
        } while (step < (s32)whole_steps);
    }
    return (u32)(pitch_low + (((u32)(pitch_high - pitch_low) >> 5) * note_offset)) >> 12;
}
