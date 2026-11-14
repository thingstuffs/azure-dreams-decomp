#include "common.h"
#include "slus/audio_update_guard_data.h"
#include "engine/audio/sequence.h"
#include "sdk/libapi.h"
#include "slus/data.h"
#include "slus/audio_timer_setup_guard_data.h"

/* S_800737C0: critical-section guard; the shared compiler view retains
 * hi/lo addressing across this event family. */
/* S_80085F9C: single s32 event handle (as returned by OpenEvent),
 * forced hi/lo access via size > 8. */
/* single s32 "mode" flag, forced hi/lo access via size > 8 (shared with
 * sibling functions in this family, e.g. sound_tick_guarded_periodic_update/sound_run_guarded_sequence_update). */

extern s32 DisableEvent(s32 event);

/* Stops the periodic-update counter, closes its event, and clears the mode and critical-section flags. */
void close_timer_2_update_event(void)
{
    audio_timer_setup_guard.value = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    DisableEvent(audio_timer_event_handle[0]);
    CloseEvent(audio_timer_event_handle[0]);
    ExitCriticalSection();
    audio_update_guard.value = 0;
    audio_timer_setup_guard.value = 0;
}
