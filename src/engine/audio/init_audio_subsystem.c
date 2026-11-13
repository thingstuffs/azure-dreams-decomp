#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"
#include "engine/audio/slots.h"
#include "slus/data.h"
#include "slus.h"

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
    set_spu_cd_or_ext_volume(0, 0, 0);
    set_cd_audio_mix_mode(2);
    reset_audio_status();
    init_audio_staging_buffers();
    clear_audio_command_queue();
    service_audio_timer_callback();
}
