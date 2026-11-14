#include "common.h"
#include "slus/audio_update_guard_data.h"
#include "engine/audio/sequence.h"
#include "sdk/libapi.h"
#include "slus/audio_timer_setup_guard_data.h"

/* S_800737C0: a plain s32 flag/mutex scalar. The shared record view has
 * padding (size > 8B) to force hi/lo access while keeping gcc from CSE-ing
 * a materialized base register (retail re-issues %hi/%lo per store) -
 * matches the sibling functions close_timer_2_update_event / open_timer_2_update_event that also
 * touch this same global. */

/* Stops hardware timer 2 in a critical section, then clears the mode and lock flags. */
void stop_timer_2_updates(void)
{
    audio_timer_setup_guard.value = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    ExitCriticalSection();
    audio_update_guard.value = 0;
    audio_timer_setup_guard.value = 0;
}
