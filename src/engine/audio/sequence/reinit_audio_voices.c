#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"
#include "engine/audio.h"

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void reinit_audio_voices(void)
{
    flush_pending_sound_voice_flags();
    key_off_active_voices(0);
    audio_disable_reverb();
    SpuClearReverbWorkArea(4);
    enable_spu_reverb();
}
