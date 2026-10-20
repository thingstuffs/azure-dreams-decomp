#include "common.h"

extern int D_800847D4[3]; /* size > 8 to force %hi/%lo addressing (see gp-vs-hilo notes) */

extern void process_first_pending_sound_channel(void);
extern void func_800544A4(void);
extern void service_audio_events(void);

/* Reactivates a pending locked channel and updates audio tasks. */
void service_audio_channels(void)
{
    if (D_800847D4[0] & 0xFF000000) {
        process_first_pending_sound_channel();
    }
    func_800544A4();
    service_audio_events();
}
