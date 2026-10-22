/* Conversions between sample-relative notes, fine tuning and SPU pitch values. */
#include "engine/audio/sound_pitch_conversions.h"
#include "engine/audio.h"



/* Scales a pitch by a fractional note offset, interpolating between adjacent steps. */
u32 _spu_2pitch(s32 pitch, u32 note_offset)
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

/* Converts a note and fine offset relative to sample tuning into an SPU pitch, capped at 0x3FFF. */
u32 _spu_note2pitch(u16 center_note, u16 center_fine, u16 note, u16 fine)
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

/* Converts an SPU pitch to a packed note and fine offset relative to the sample's center tuning. */
u32 _spu_pitch2note(u16 center_note, u16 center_fine, u16 pitch)
{
    u16 inverted_pitch;
    s32 top_bit;
    s32 octave;
    s32 octave_pitch;
    u32 scale;
    u32 row_base;
    u32 row_end;
    u32 pitch_step;
    u32 lower_offset;
    u32 upper_offset;
    u32 lower_pitch;
    u32 upper_pitch;
    u32 lower_fixed;
    u32 upper_fixed;
    s32 scan_index;
    s32 slot;
    s32 pitch_index;
    s32 row_index;
    s32 note_offset;
    s32 fine_offset;
    s32 note;
    s32 fine;

    inverted_pitch = (~(s32)pitch) & 0xFFFF;
    top_bit = 0;
    for (scan_index = 15; scan_index >= 0; scan_index--) {
        if (((inverted_pitch >> scan_index) & 1) == 0) {
            top_bit = scan_index;
            break;
        }
    }
    octave = top_bit - 12;
    octave_pitch = 1 << top_bit;
    scale = 0x1000;
    for (scan_index = 0; scan_index < 0x30; scan_index++) {
        row_base = (u32)octave_pitch * scale;
        scale *= 0x103B;
        scale >>= 12;
        row_end = (u32)octave_pitch * scale;
        pitch_step = (row_end - row_base) >> 5;
        slot = 0;
        row_index = scan_index * 32;
        lower_offset = 0;
        upper_offset = pitch_step;
        for (; slot < 0x20; slot++) {
            lower_fixed = row_base + lower_offset;
            upper_fixed = row_base + upper_offset;
            lower_pitch = lower_fixed >> 12;
            upper_pitch = upper_fixed >> 12;
            if ((u32)pitch >= lower_pitch) {
                if ((u32)pitch < upper_pitch) {
                    pitch_index = row_index + slot;
                    goto done;
                }
            }
            upper_offset += pitch_step;
            lower_offset += pitch_step;
        }
    }
    pitch_index = 1536;
done:
    note_offset = pitch_index / 128;
    fine_offset = pitch_index - note_offset * 128;
    note = (s32)center_note + note_offset + octave * 12;
    fine = (s32)center_fine + fine_offset;
    return (u32)((note << 8) | fine);
}
