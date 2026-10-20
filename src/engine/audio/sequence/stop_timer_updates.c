#include "common.h"

/* S_800737C0: a plain s32 flag/mutex scalar. Declared as a struct with
 * padding (size > 8B) to force hi/lo access while keeping gcc from CSE-ing
 * a materialized base register (retail re-issues %hi/%lo per store) -
 * matches the sibling functions close_timer_2_update_event / open_timer_2_update_event that also
 * touch this same global. */
typedef struct {
    /* 0x00 */ s32 v;
    /* 0x04 */ s32 pad[2];
} S_800737C0;

extern S_800737C0 audio_timer_setup_guard;
extern s32 audio_update_guard[4]; /* forced hi/lo access via size > 8 */

extern s32 EnterCriticalSection(void);
extern s32 ExitCriticalSection(void);
extern void StopRCnt(s32 a0);

/* Stops hardware timer 2 in a critical section, then clears the mode and lock flags. */
void stop_timer_2_updates(void)
{
    audio_timer_setup_guard.v = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    ExitCriticalSection();
    audio_update_guard[0] = 0;
    audio_timer_setup_guard.v = 0;
}
