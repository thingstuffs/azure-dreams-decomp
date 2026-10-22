#ifndef SLUS_SOUND_PITCH_CONVERSIONS_H
#define SLUS_SOUND_PITCH_CONVERSIONS_H

#include "common.h"

extern int abs(int);
u32 _spu_note2pitch(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 _spu_pitch2note(u16 center_note, u16 center_fine, u16 pitch);

u32 _spu_2pitch(s32 pitch, u32 note_offset);

#endif
