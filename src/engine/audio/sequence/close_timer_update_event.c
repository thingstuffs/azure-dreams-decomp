#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* S_800737C0: single s32 "critical-section active" flag, forced hi/lo
 * access via size > 8 (extern-array trick shared with sibling functions
 * in this family, e.g. open_timer_2_update_event). */
extern s32 audio_timer_setup_guard[4];
/* S_80085F9C: single s32 event handle (as returned by OpenEvent),
 * forced hi/lo access via size > 8. */
/* single s32 "mode" flag, forced hi/lo access via size > 8 (shared with
 * sibling functions in this family, e.g. sound_tick_guarded_periodic_update/sound_run_guarded_sequence_update). */
extern s32 audio_update_guard[4];

extern s32 EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void StopRCnt(s32 arg);
extern s32 DisableEvent(s32 event);
extern s32 CloseEvent(s32 event);

/* Stops the periodic-update counter, closes its event, and clears the mode and critical-section flags. */
void close_timer_2_update_event(void)
{
    audio_timer_setup_guard[0] = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    DisableEvent(audio_timer_event_handle[0]);
    CloseEvent(audio_timer_event_handle[0]);
    ExitCriticalSection();
    audio_update_guard[0] = 0;
    audio_timer_setup_guard[0] = 0;
}
