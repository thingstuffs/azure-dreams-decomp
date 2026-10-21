#ifndef ENGINE_AUDIO_SPU_H
#define ENGINE_AUDIO_SPU_H
/* Prototypes of the functions defined in src/engine/audio/spu/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/spu_voice.h"

struct S_800799BC;
struct SoundReverbParameters;

/* SpuQuit.c */
void stop_spu_dma_event_service(void);

/* audio_get_whether_non_skipped_block_contains_address_starts_beyond.c */
s32 initialize_sound_transfer_range(s32 count, struct S_800799BC *record);
s32 audio_get_whether_non_skipped_block_contains_address_starts_beyond(u32 address);
s32 test_spu_blocks_beyond_address(u32 value);

/* audio_handle_optionally_aligns_shifts_stores_returns_result.c */
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 index, u32 value);

/* clamp_and_submit_driver_parameter.c */
s32 clamp_and_submit_driver_parameter(s32 voice, u32 rate);
s32 lookup_and_scale_driver_address(s32 address);
s32 poll_driver_completion_event(s32 wait_for_completion);

/* jtbl.c */
s32 read_selected_voice_key_state(s32 voice_mask);
void apply_spu_voice_attributes(SpuVoiceAttr_ *attr);
void read_spu_voice_attributes(SpuVoiceAttr_ *voice_attr);

/* query_driver_halfword_pair.c */
s32 query_driver_halfword_pair(s16 entry_index, s16 *out_first_value, s16 *out_second_value);

/* query_driver_pair_shifted_seven.c */
s32 query_driver_pair_shifted_seven(s16 flags_index, s16 *out_first, s16 *out_second);

/* read_spu_register_pair.c */
s32 func_8005E7B0(s32 low_index, s32 high_index);
s32 read_spu_register_pair(s32 low_index, s32 high_index);

/* sound_event_start.c */
void start_spu_dma_event_service(void);

/* sound_register_helpers.c */
void func_8005D550(s32 index, u32 value, s32 apply_shift);
void store_u16_table_entry(s32 index, u32 value, s32 apply_shift);
s32 load_u16_table_entry_scaled(s32 index, s32 shift_mode);
void set_driver_status_bits(s32 use_status_3);

/* sound_reset_state.c */
void reset_spu_runtime_and_start_event_service(s32 channel);
s32 set_reverb_address_available(s32 enabled);

/* sound_reverb_writer.c */
void write_spu_reverb_parameters(struct SoundReverbParameters *source);

/* spu_attr.c */
s32 set_spu_reverb_enabled_if_available(s32 enable);

/* submit_driver_halfword_pair.c */
s32 submit_driver_halfword_pair(s16 flags_index, s16 first_value, s16 second_value);

/* submit_driver_seven_bit_pair.c */
s32 submit_driver_seven_bit_pair(s32 flag_index, s32 first_value, s32 second_value);

/* submit_driver_transfer_with_fallback.c */
s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param);
s32 submit_driver_transfer_mode_zero(s32 buffer_addr, s32 size);

#endif
