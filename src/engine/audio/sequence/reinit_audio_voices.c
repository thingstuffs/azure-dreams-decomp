#include "common.h"

extern void flush_pending_sound_voice_flags(void);
extern void dispatch_combined_driver_flags(int unused);
extern void audio_disable_reverb(void);
extern void func_8005E7E0(int voice);
extern void enable_available_spu_reverb(void);

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void reinit_audio_voices(void)
{
    flush_pending_sound_voice_flags();
    dispatch_combined_driver_flags(0);
    audio_disable_reverb();
    func_8005E7E0(4);
    enable_available_spu_reverb();
}
