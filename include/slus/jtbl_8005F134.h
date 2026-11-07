#ifndef SLUS_JTBL_8005F134_H
#define SLUS_JTBL_8005F134_H
#include "sdk/libspu.h"

#include "common.h"
#include "shared/spu_voice.h"

extern volatile u16 *spu_registers;
extern u16 spu_voice_sample_notes[24];
extern s32 spu_active_voice_mask;
extern s32 spu_address_unit_shift;

u32 _spu_note2pitch(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 _spu_pitch2note(u16 center_note, u16 center_fine, u16 pitch);

#endif
