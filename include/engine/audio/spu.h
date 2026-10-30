#ifndef ENGINE_AUDIO_SPU_H
#define ENGINE_AUDIO_SPU_H
/* Prototypes of the functions defined in src/engine/audio/spu/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/spu_voice.h"

struct S_800799BC;
struct SoundReverbParameters;

/* SpuQuit.c */
void SpuQuit(void);

/* audio_get_whether_non_skipped_block_contains_address_starts_beyond.c */
s32 SpuInitMalloc(s32 count, struct S_800799BC *record);
s32 _SpuIsInAllocateArea(u32 address);
s32 _SpuIsInAllocateArea_(u32 value);

/* audio_handle_optionally_aligns_shifts_stores_returns_result.c */
s32 _spu_FsetRXXa(s32 index, u32 value);

/* clamp_and_submit_driver_parameter.c */
s32 write_spu_transfer_data(s32 data, u32 size);
s32 SpuSetTransferStartAddr(s32 address);
s32 SpuIsTransferCompleted(s32 wait_for_completion);

/* jtbl.c */
s32 SpuGetKeyStatus(s32 voice_mask);
void apply_spu_voice_attributes(SpuVoiceAttr_ *attr);
void SpuGetVoiceAttr(SpuVoiceAttr_ *voice_attr);

/* query_driver_halfword_pair.c */
s32 query_driver_halfword_pair(s16 entry_index, s16 *out_first_value, s16 *out_second_value);

/* query_driver_pair_shifted_seven.c */
s32 query_driver_pair_shifted_seven(s16 flags_index, s16 *out_first, s16 *out_second);

/* read_spu_register_pair.c */
s32 func_8005E7B0(s32 low_index, s32 high_index);
s32 read_spu_register_pair(s32 low_index, s32 high_index);

/* sound_event_start.c */
void SpuStart(void);

/* sound_register_helpers.c */
void func_8005D550(s32 index, u32 value, s32 apply_shift);
void _spu_FsetRXX(s32 index, u32 value, s32 apply_shift);
s32 _spu_FgetRXXa(s32 index, s32 shift_mode);
void _spu_FsetPCR(s32 use_status_3);

/* sound_reset_state.c */
void _SpuInit(s32 channel);
s32 SpuReserveReverbWorkArea(s32 enabled);

/* sound_reverb_writer.c */
void _spu_setReverbAttr(struct SoundReverbParameters *source);

/* spu_attr.c */
s32 SpuSetReverb(s32 enable);

/* submit_driver_halfword_pair.c */
s32 submit_driver_halfword_pair(s16 flags_index, s16 first_value, s16 second_value);

/* submit_driver_seven_bit_pair.c */
s32 submit_driver_seven_bit_pair(s32 flag_index, s32 first_value, s32 second_value);

/* submit_driver_transfer_with_fallback.c */
s32 _spu_Fw(s32 channel, s32 playback_param);
s32 _spu_Fr(s32 buffer_addr, s32 size);

#endif
