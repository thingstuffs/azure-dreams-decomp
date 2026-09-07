#include "common.h"

/* S_800737C0: single s32 "critical-section active" flag, forced hi/lo
 * access via size > 8 (extern-array trick shared with sibling functions
 * in this family, e.g. func_800585A0). */
extern s32 D_800737C0[4];
/* S_80085F9C: single s32 event handle (as returned by OpenEvent),
 * forced hi/lo access via size > 8. */
extern s32 D_80085F9C[4];
/* single s32 "mode" flag, forced hi/lo access via size > 8 (shared with
 * sibling functions in this family, e.g. func_80058510/func_80058700). */
extern s32 D_80085F98[4];

extern s32 EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void StopRCnt(s32 arg);
extern s32 DisableEvent(s32 event);
extern s32 CloseEvent(s32 event);

/* Tears down the periodic-update event: enters a critical section, disables
 * and closes the event registered in D_80085F9C, exits the critical
 * section, then clears the mode flag (D_80085F98) and the
 * critical-section-active flag (D_800737C0). */
void func_8005863C(void)
{
    D_800737C0[0] = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    DisableEvent(D_80085F9C[0]);
    CloseEvent(D_80085F9C[0]);
    ExitCriticalSection();
    D_80085F98[0] = 0;
    D_800737C0[0] = 0;
}
