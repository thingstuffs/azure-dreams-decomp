#include "common.h"

extern int abs(int);

/* Convert a note and fine tuning relative to the center note into a clamped SPU pitch. */
u32 func_8005F7D0(u16 center_note, u16 center_fine, u16 note, u16 fine)
{
    s32 center_tuning;
    /* 8 bytes of frame below reload's spill slot: retail's product carrier
     * spills to 8($sp) in a 16-byte frame (see MATCH receipt). */
    s32 frame_pad[2];
    s32 pitch_value;
    s32 note_distance;
    s32 octaves;
    s32 octave_offset;
    s32 base_pitch;
    s32 fine_offset;
    s32 step_index;
    s32 lower_pitch;
    s32 upper_pitch;
    u32 pitch_steps;
    u32 step_fraction;
    u32 pitch_scale;
    u32 pitch;

    center_tuning = ((s32)center_note << 7) + center_fine;
    pitch_value = (((s32)note << 7) + fine) - center_tuning;
    note_distance = pitch_value;
    if (pitch_value < 0) {
        note_distance = -pitch_value;
    }
    octaves = note_distance / 1536;
    octave_offset = note_distance % 1536;
    if (pitch_value >= 0) {
        base_pitch = 0x1000 << octaves;
    } else {
        if (octave_offset != 0) {
            octaves++;
            octave_offset = 1536 - octave_offset;
        }
        base_pitch = 0x1000 >> octaves;
    }
    pitch_value = (s32)((u32)base_pitch & 0xFFFF);
    pitch_scale = 0x103B;
    lower_pitch = (s32)((u32)pitch_value << 12);
    fine_offset = abs(octave_offset);
    pitch_steps = (u32)fine_offset >> 5;
    step_fraction = (u32)fine_offset & 0x1F;
    upper_pitch = pitch_value * pitch_scale;
    step_index = 0;
    if (pitch_steps != 0) {
        do {
            lower_pitch = pitch_value * pitch_scale;
            pitch_scale *= 0x103B;
            pitch_scale >>= 12;
            step_index++;
            upper_pitch = pitch_value * pitch_scale;
        } while (step_index < (s32)pitch_steps);
    }
    pitch = (u32)(lower_pitch + (((u32)(upper_pitch - lower_pitch) >> 5) * step_fraction)) >> 12;
    if (pitch >= 0x4000) {
        pitch = 0x3FFF;
    }
    return pitch & 0xFFFF;
}
