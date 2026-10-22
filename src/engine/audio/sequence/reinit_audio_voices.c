#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

extern void dispatch_combined_driver_flags(int unused);

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void reinit_audio_voices(void)
{
    flush_pending_sound_voice_flags();
    dispatch_combined_driver_flags(0);
    audio_disable_reverb();
    SpuClearReverbWorkArea(4);
    enable_available_spu_reverb();
}
