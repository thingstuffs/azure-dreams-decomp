#include "common.h"
#include "slus/audio_update_guard_data.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"
#include "slus/audio_timer_setup_guard_data.h"
#include "sdk/libapi.h"

/* D_800737C0: "in-progress" guard flag for the RCnt/event init sequence.
 * The shared compiler view retains hi/lo addressing. */
/* D_80085F9C: stores the event handle returned by OpenEvent. */
/* D_80085F98: mode/status flag, cleared at the end of the init sequence. */

/* Set up the root counter interrupt event and start the counter unless setup is in progress. */
void open_timer_2_update_event(void)
{
    if (audio_timer_setup_guard.value == 0) {
        audio_timer_setup_guard.value = 1;
        EnterCriticalSection();
        audio_timer_event_handle[0] = OpenEvent(0xF2000002, 2, 0x1000, sound_tick_guarded_periodic_update);
        EnableEvent(audio_timer_event_handle[0]);
        SetRCnt(0xF2000002, 0x1C00, 0x1000);
        StartRCnt(0xF2000002);
        ExitCriticalSection();
        audio_update_guard.value = 0;
        audio_timer_setup_guard.value = 0;
    }
}
