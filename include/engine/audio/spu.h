#ifndef ENGINE_AUDIO_SPU_H
#define ENGINE_AUDIO_SPU_H

#include "common.h"
#include "sdk/libspu.h"
#include "shared/spu_voice.h"

/* Existing C interfaces with unresolved library attribution. */
s32 write_spu_transfer_data(s32 data, u32 size);
void apply_spu_voice_attributes(SpuVoiceAttr_ *attr);
s32 query_driver_halfword_pair(s16 entry_index, s16 *out_first_value, s16 *out_second_value);
s32 query_driver_pair_shifted_seven(s16 flags_index, s16 *out_first, s16 *out_second);
s32 func_8005E7B0(s32 low_index, s32 high_index);
s32 read_spu_register_pair(s32 low_index, s32 high_index);
s32 submit_driver_halfword_pair(s16 flags_index, s16 first_value, s16 second_value);
s32 submit_driver_seven_bit_pair(s32 flag_index, s32 first_value, s32 second_value);

#endif
