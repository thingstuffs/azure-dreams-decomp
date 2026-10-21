#ifndef SLUS_JTBL_8005F134_H
#define SLUS_JTBL_8005F134_H

#include "common.h"
#include "shared/spu_voice.h"

extern volatile u16 *spu_registers;
extern u16 spu_voice_sample_notes[24];
extern s32 spu_active_voice_mask;
extern s32 spu_address_unit_shift;

u32 calculate_pitch_from_note(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 sound_convert_pitch_to_packed_note(u16 center_note, u16 center_fine, u16 pitch);
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 reg, u32 val);
s32 read_selected_voice_key_state(s32 voice_mask);
void apply_spu_voice_attributes(SpuVoiceAttr_ *attr);
void read_spu_voice_attributes(SpuVoiceAttr_ *voice_attr);

#endif
