#ifndef ENGINE_AUDIO_SEQUENCE_H
#define ENGINE_AUDIO_SEQUENCE_H
/* Prototypes of the functions defined in src/engine/audio/sequence/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* audio_sequence_slots: allocate_sequence_bank_slot registers a recognized
 * sequence header, and sound_activate_loaded_sequence_slot reads that same
 * header word into audio_sequence_data_base. All table walks use 0x0C-byte
 * records. reset_sound_slots initializes 16 entries; ordinary callers keep
 * their existing 8-entry extern bounds. The gain fields retain unsigned
 * halfword accesses; signed gain projections are separate. */
typedef struct SoundSequenceSlot {
    /* 0x00 */ s16 sequence_id; /* -1 marks a free entry */
    /* 0x02 */ s16 state;
    /* 0x04 */ s32 data_address; /* integer representation is intentional */
    /* 0x08 */ u16 left_gain;
    /* 0x0A */ u16 right_gain;
} SoundSequenceSlot;

struct PlaybackState;
struct S_80055E84;
struct S_80056654_0;
struct S_80056800_0;
struct S_800590E0;

/* activate_sequence_slot.c */
void activate_sequence_slot(s16 slot_index);

/* audio_apply_channel_control.c */
void audio_apply_channel_control(u8 channel, u8 control, u32 value);

/* audio_configure_explicit_voice.c */
s16 audio_configure_explicit_voice(s16 sound_id, s32 voice_id, s16 note, unsigned short note_offset, u16 pitch, u16 left_volume, u16 right_volume);

/* audio_get_current_bank_tone_record.c */
s32 audio_get_current_bank_tone_record(s32 *row, s32 column);

/* audio_initialize_resident_sequence.c */
void audio_initialize_resident_sequence(void);

/* audio_refresh_all_voice_volumes.c */
void audio_refresh_all_voice_volumes(void);

/* audio_refresh_sequence_voice_volumes.c */
void audio_refresh_sequence_voice_volumes(void);

/* audio_reset_all_voices.c */
void audio_reset_all_voices(void);

/* audio_reset_and_release_sequence_banks.c */
void audio_reset_and_release_sequence_banks(void);

/* audio_reset_sequence_subsystem.c */
void audio_reset_sequence_subsystem(void);

/* audio_reset_sequence_tracks_and_channels.c */
void audio_reset_sequence_tracks_and_channels(void);

/* audio_sequence_note_off.c */
void audio_sequence_note_off(s32 first_key, s32 second_key);

/* audio_stop_effect_voice.c */
s32 audio_stop_effect_voice(s16 slot_id);

/* audio_stop_matching_effect_voices.c */
void audio_stop_matching_effect_voices(s32 packed_key, s32 packed_channel);

/* audio_tick_sequence_tracks.c */
s32 audio_tick_sequence_tracks(void);

/* audio_update_voice_pitch.c */
void audio_update_voice_pitch(struct S_80056654_0 *state, s32 force_update);

/* audio_update_voice_tremolo.c */
void audio_update_voice_tremolo(struct S_80055E84 *voice);

/* close_timer_update_event.c */
void close_timer_2_update_event(void);

/* compare_byte_span.c */
s32 compare_byte_span(u8 *p1, u8 *p2, s32 n);

/* decode_note_text.c */
void *decode_fullwidth_text(void *entries, u8 *text, s32 initial_octave);

/* entry_compare_byte_span.c */
s32 find_sequence_magic_after_offset(s32 start_index);

/* find_sequence_tag.c */
s32 find_sequence_tag(s32 start_index);

/* get_sequence_play_state.c */
s32 get_sequence_play_state(void);

/* init_sequence_playback.c */
s32 init_sequence_playback(void);

/* open_timer_update_event.c */
void open_timer_2_update_event(void);

/* playback_set_next.c */
s32 seek_sequence_tag_and_schedule_step(struct PlaybackState *state);

/* read_base_vlq.c */
s32 read_base_128_vlq(s32 stream);

/* read_big_endian_word.c */
u32 read_big_endian_word(s32 stream);

/* read_sequence_halfword.c */
int read_sequence_halfword(int input);

/* reinit_audio_voices.c */
void reinit_audio_voices(void);

/* scale_value_with_remainder_second.c */
s32 initialize_audio_sequence_tracks(void);

/* scan_stream_for_three_byte_marker.c */
s32 scan_stream_for_three_byte_marker(s32 offset);

/* set_playback_note.c */
void set_playback_note(s32 note);

/* set_sound_slot_byte_pair.c */
void set_sound_slot_byte_pair(s16 index, s32 value_8, s32 value_a);

/* skip_vlq_payload_until_f.c */
void skip_vlq_payload_until_f_7(struct S_800590E0 *stream);

/* sound_activate_loaded_sequence_slot.c */
void sound_activate_loaded_sequence_slot(s16 slot_index, u8 mode, s16 sub_id);

/* sound_apply_changed_voice_volume_offsets.c */
void sound_apply_changed_voice_volume_offsets(void);

/* sound_assign_sequence_payload_slot.c */
void assign_sound_payload_and_release_channel(s32 event);

/* sound_free_sequence_slot.c */
void sound_free_sequence_slot(s32 slot_id);

/* sound_reset_indexed_voice_envelope.c */
void sound_reset_indexed_voice_envelope(s32 request_index);

/* sound_reset_indexed_voice_envelope_second.c */
void start_sound_effect_program_voices(s32 bank_program, s32 note_pitch, s16 left_gain, s16 right_gain, s32 force_effect);

/* sound_reset_sequence_slot_to_idle.c */
void sound_reset_sequence_slot_to_idle(s16 slot_index);

/* sound_run_guarded_sequence_update.c */
void sound_run_guarded_sequence_update(void);

/* sound_set_indexed_voice_volumes.c */
s32 sound_set_indexed_voice_volumes(s32 table_index, s16 field_8_value, s16 field_a_value);

/* sound_set_seven_bit_channel_value_and_notify.c */
void sound_set_seven_bit_channel_value_and_notify(u8 index, s32 unused, s32 value);

/* sound_step_bipolar_oscillation.c */
void sound_step_bipolar_oscillation(struct S_80056800_0 *state);

/* sound_step_clamped_signed_ramp.c */
void sound_step_clamped_signed_ramp(void *state);

/* sound_tick_guarded_periodic_update.c */
long long sound_tick_guarded_periodic_update(void);

/* sound_update_voice_modulation_slots.c */
void sound_update_voice_modulation_slots(void);

/* start_channel_note.c */
void start_channel_note(u8 channel_id, s16 note, u8 velocity);

/* start_sequence_in_free_slot.c */
s16 start_sequence_in_free_slot(s16 bank, s16 program, s16 tone, s16 note, s16 fine_note, s16 left_gain, s16 right_gain);

/* stop_timer_updates.c */
void stop_timer_2_updates(void);

/* suspend_sequence_slot.c */
void suspend_sequence_slot(s16 slot_index);

/* update_sequence_slot_state.c */
s16 update_sequence_slot_state(s16 entry_index);

#endif
