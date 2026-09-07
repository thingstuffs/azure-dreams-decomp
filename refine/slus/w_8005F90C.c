#include "common.h"

/* Convert SPU pitch to a packed note and fine value relative to the center note and fine offset. */
u32 func_8005F90C(u16 center_note, u16 center_fine, u16 pitch)
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
