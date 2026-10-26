#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* D_800737C0: "in-progress" guard flag for the RCnt/event init sequence.
 * hi/lo access (lui/lw with %hi/%lo, not gp_rel) -> size must be > 8 bytes. */
extern s32 audio_timer_setup_guard[4];
/* D_80085F9C: stores the event handle returned by OpenEvent. */
/* D_80085F98: mode/status flag, cleared at the end of the init sequence. */
extern s32 audio_update_guard[4];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern s32 OpenEvent(u32 class, s32 spec, s32 mode, void (*func)(void));
extern s32 EnableEvent(u32 event);
extern s32 SetRCnt(u32 spec, u16 target, s32 mode);
extern s32 StartRCnt(u32 spec);

/* Set up the root counter interrupt event and start the counter unless setup is in progress. */
void open_timer_2_update_event(void)
{
    if (audio_timer_setup_guard[0] == 0) {
        audio_timer_setup_guard[0] = 1;
        EnterCriticalSection();
        audio_timer_event_handle[0] = OpenEvent(0xF2000002, 2, 0x1000, sound_tick_guarded_periodic_update);
        EnableEvent(audio_timer_event_handle[0]);
        SetRCnt(0xF2000002, 0x1C00, 0x1000);
        StartRCnt(0xF2000002);
        ExitCriticalSection();
        audio_update_guard[0] = 0;
        audio_timer_setup_guard[0] = 0;
    }
}
