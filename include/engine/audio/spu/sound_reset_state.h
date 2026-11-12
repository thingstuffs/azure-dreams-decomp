#ifndef SLUS_SOUND_RESET_STATE_H
#define SLUS_SOUND_RESET_STATE_H
#include "sdk/libspu.h"

#include "engine/audio/spu/sound_range_records.h"
#include "engine/audio/spu/reverb_start_address.h"
#include "engine/audio/spu/voice_sample_notes.h"

extern s32 spu_reverb_start_addresses[10];
extern s32 spu_reverb_enabled;
extern s32 spu_reverb_range_override;
extern s32 spu_reverb_mode;
extern u16 spu_reverb_depth_left;
extern u16 spu_reverb_depth_right;
extern s32 spu_reverb_delay;
extern s32 spu_reverb_feedback;
extern s32 spu_transfer_completion_override;
extern s32 spu_transfer_uses_fifo;
extern s32 spu_active_voice_mask;
extern s32 spu_register_dirty_flags;
extern s32 spu_buffered_voice_mask;
extern s32 spu_register_buffer_flags;
void ResetCallback(s32 channel);
s32 _spu_init(s32 warm);


#endif
