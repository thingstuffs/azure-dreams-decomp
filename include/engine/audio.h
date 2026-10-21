#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H
/* Prototypes of the functions defined in src/engine/audio/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sound_volume.h"

struct S_80053374_obj;
struct S_80054538;
struct S_800545F4;
struct S_80055ADC_arg0;

/* activate_pending_playback.c */
void activate_pending_playback(void);

/* audio_dispatch_stream_request.c */
void audio_dispatch_stream_request(s32 message);

/* audio_dispatch_stream_request_second.c */
void drain_audio_commands_and_service_channels(void);

/* audio_handle_stream_control_event.c */
void audio_handle_stream_control_event(s32 event);

/* audio_handle_stream_control_event_second.c */
void update_cd_stream_ramp_and_completion(void);

/* audio_load_sound_effect_bank.c */
void audio_load_sound_effect_bank(s16 record_id);

/* build_record_pointer_table.c */
void build_record_pointer_table(struct S_80055ADC_arg0 *recordBlock, u32 tableIndex);

/* check_cd_stream_end.c */
void check_cd_stream_end(void);

/* decode_audio_selector.c */
void decode_audio_selector(s32 selector);

/* dispatch_audio_command.c */
void dispatch_audio_command(s32 code);

/* dispatch_audio_event.c */
void dispatch_audio_event(s32 event);

/* dispatch_combined_driver_flags.c */
void dispatch_combined_driver_flags(void);

/* entry_release_enabled_sound_channel.c */
void release_sound_channel_and_mark_pending(s16 channel);

/* entry_set_cd_audio_mix_mode.c */
void dispatch_audio_mix_action(s32 action);

/* entry_test_sound_channel_availability.c */
void stop_flagged_sound_voices(void);

/* find_sound_table_entry.c */
u32 *find_sound_table_entry(s32 sound_id);

/* get_volume_scale_by_selector.c */
s32 get_volume_scale_by_selector(s32 selector);

/* handle_audio_status_code.c */
void handle_audio_status_code(u8 code);

/* init_audio_staging_buffers.c */
void init_audio_staging_buffers(void);

/* init_audio_subsystem.c */
void init_audio_subsystem(void);

/* play_sound_unless_mode_two.c */
short dispatch_sound_word_unless_disabled(int inputValue);

/* pop_audio_queue.c */
u16 pop_audio_queue(void);

/* process_first_pending_sound_channel.c */
void process_first_pending_sound_channel(void);

/* read_capped_audio_meter.c */
s32 read_capped_audio_meter(void);

/* release_enabled_sound_channel.c */
void release_enabled_sound_channel(s16 channel);

/* reset_audio_command_state.c */
void reset_audio_command_state(void);

/* reset_audio_status.c */
void reset_audio_status(void);

/* scene_initialize_sixteen_sprite_sequence.c */
void scene_initialize_sixteen_sprite_sequence(struct S_80053374_obj *entity, void *owner);

/* select_marker_table.c */
void select_marker_table(s32 marker_code);

/* service_audio_channels.c */
void service_audio_channels(void);

/* service_audio_events.c */
void service_audio_events(void);

/* service_audio_timer.c */
void service_audio_timer(void);

/* set_cd_audio_mix_mode.c */
void set_cd_audio_mix_mode(unsigned char mix_mode);

/* set_sound_task_priority.c */
void func_80054F9C(s32 pad_event, SoundTask *task);
void set_sound_task_priority(s32 pad_event, SoundTask *task);

/* set_volume_scale_by_selector.c */
void set_volume_scale_by_selector(s16 value, s32 stat_index);

/* sound_assign_sequence_payload_slot.c */
void sound_assign_sequence_payload_slot(s32 selector);

/* sound_begin_cd_playback_setup.c */
void sound_begin_cd_playback_setup(void);

/* sound_check_or_wait_for_spu_transfer.c */
s16 sound_check_or_wait_for_spu_transfer(s16 wait_for_completion);

/* sound_get_cd_sector_position.c */
int sound_get_cd_sector_position(void);

/* sound_load_pending_bank_slot.c */
void sound_load_pending_bank_slot(s16 entry_id);

/* sound_scale_pitch_by_fractional_note.c */
u32 sound_scale_pitch_by_fractional_note(s32 pitch, u32 note_offset);
u32 calculate_pitch_from_note(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 sound_convert_pitch_to_packed_note(u16 center_note, u16 center_fine, u16 pitch);

/* sound_set_sequence_volume_scale.c */
void sound_set_sequence_volume_scale(s16 new_value);

/* sound_set_spu_master_volume.c */
void sound_set_spu_master_volume(s32 left_volume, s32 right_volume);

/* sound_start_scaled_primary_and_secondary_voices.c */
void sound_start_scaled_primary_and_secondary_voices(s32 target_id, void *target_data);

/* sound_stream_load.c */
s32 func_8004437C(s16 entry_index, s16 mode);
s32 select_sound_stream(s16 entry_index, s16 mode);
s32 func_8004450C(s16 state_index);
s32 load_sound_set(s16 state_index);

/* start_pending_selection.c */
void start_pending_selection(void);

/* stop_audio_playback.c */
void stop_audio_playback(void);

/* submit_scaled_driver_halfword_pair.c */
void submit_scaled_driver_halfword_pair(s32 mode, s32 value_1, s32 value_2);

/* submit_scaled_driver_halfword_pair_second.c */
void apply_scaled_cd_stream_volume(void);

/* submit_tagged_driver_byte.c */
void submit_tagged_driver_byte(u8 type_group, u8 type_variant, u8 value);

/* test_sound_channel_availability.c */
s32 test_sound_channel_availability(s16 bit_index);

/* update_audio_fade.c */
s32 update_audio_fade(struct S_800545F4 *gauge);

/* update_audio_ramp.c */
void update_audio_ramp(struct S_80054538 *ramp);

/* update_cd_stream_flags.c */
void update_cd_stream_flags(void);

/* wait_until_sound_idle.c */
void func_80044698(void);
void wait_until_sound_idle(void);

/* Data declarations. */
extern s8 sound_stream_state_index;

#endif
