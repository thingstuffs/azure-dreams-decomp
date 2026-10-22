#ifndef SLUS_SOUND_RESET_STATE_H
#define SLUS_SOUND_RESET_STATE_H

#include "engine/audio/spu/sound_range_records.h"

extern s32 spu_reverb_start_addresses[10];
extern s16 spu_voice_sample_notes[24];
extern s32 spu_reverb_enabled;
extern s32 spu_reverb_range_override;
extern s32 spu_reverb_mode;
extern u16 spu_reverb_depth_left;
extern u16 spu_reverb_depth_right;
extern s32 spu_reverb_delay;
extern s32 spu_reverb_feedback;
extern u32 spu_reverb_start_address;
extern s32 spu_transfer_completion_override;
extern s32 spu_transfer_uses_fifo;
extern s32 spu_active_voice_mask;
extern s32 spu_register_dirty_flags;
extern s32 spu_buffered_voice_mask;
extern s32 spu_register_buffer_flags;
void ResetCallback(s32 channel);
s32 _spu_init(s32 warm);
void SpuStart(void);
void _spu_FsetRXX(s32 index, u32 value, s32 apply_shift);

void _SpuInit(s32 channel);
s32 SpuReserveReverbWorkArea(s32 enabled);

#endif
