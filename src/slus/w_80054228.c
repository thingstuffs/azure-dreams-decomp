#include "shared/sound_state.h"
#include "common.h"

/* Sibling struct (matches src/w_8005440C.c / w_80054C58.c's SoundPlaybackState for the
 * fields touched here): flags1 at 0x0. */


extern void func_800553D4(s32 a0);
extern void dispatch_combined_driver_flags();
extern void release_enabled_sound_channel(s16 a0);
extern void audio_reset_and_release_sequence_banks(void);
extern void func_8005A4B8(void);

/* Stops active playback, releases all four channels, and runs audio cleanup. */
void func_80054228(void)
{
    s16 channel;

    if (D_800847D0.flags00 & 0x100) {
        func_800553D4(0x71);
    }

    dispatch_combined_driver_flags(0);

    for (channel = 0; channel < 4; channel++) {
        release_enabled_sound_channel(channel);
    }

    audio_reset_and_release_sequence_banks();
    func_8005A4B8();
}
