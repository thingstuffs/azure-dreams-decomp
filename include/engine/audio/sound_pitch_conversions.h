#ifndef SLUS_SOUND_PITCH_CONVERSIONS_H
#define SLUS_SOUND_PITCH_CONVERSIONS_H

#include "common.h"

extern int abs(int);
u32 calculate_pitch_from_note(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 sound_convert_pitch_to_packed_note(u16 center_note, u16 center_fine, u16 pitch);

u32 sound_scale_pitch_by_fractional_note(s32 pitch, u32 note_offset);

#endif
