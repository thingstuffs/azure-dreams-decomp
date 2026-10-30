#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"
#include "engine/audio/slots.h"
#include "slus/data.h"

extern void set_audio_timer_state(s32 value);
extern void noop_audio_init_hook(void *a0, s32 a1, s32 a2);
extern void set_sound_flag_update_suppression(s16 value);
extern s32 SpuClearReverbWorkArea(s32 voice);
extern void enable_available_spu_reverb(void);
extern s32 submit_shifted_stereo_sound_parameters(s16 a0, s16 a1);
extern void clear_audio_command_queue(void);
extern void service_audio_timer_callback(void);

/* Initializes audio subsystems, buffers, and playback defaults. */
void init_audio_subsystem(void) {
    audio_reset_sequence_subsystem();
    set_audio_timer_state(1);
    set_audio_entry_count(0x18);
    noop_audio_init_hook(D_80084548, 1, 1);
    set_sound_flag_update_suppression(0);
    set_audio_bank(4);
    SpuClearReverbWorkArea(4);
    enable_available_spu_reverb();
    submit_shifted_stereo_sound_parameters(0x3C, 0x3C);
    sound_set_spu_master_volume(0x7F, 0x7F);
    submit_tagged_driver_byte(0, 0, 0);
    submit_scaled_driver_halfword_pair(0, 0, 0);
    set_cd_audio_mix_mode(2);
    reset_audio_status();
    init_audio_staging_buffers();
    clear_audio_command_queue();
    service_audio_timer_callback();
}
