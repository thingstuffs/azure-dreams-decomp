#include "common.h"

/* S_800737C0: a plain s32 flag/mutex scalar. Declared as a struct with
 * padding (size > 8B) to force hi/lo access while keeping gcc from CSE-ing
 * a materialized base register (retail re-issues %hi/%lo per store) -
 * matches the sibling functions func_8005863C / func_800585A0 that also
 * touch this same global. */
typedef struct {
    /* 0x00 */ s32 v;
    /* 0x04 */ s32 pad[2];
} S_800737C0;

extern S_800737C0 D_800737C0;
extern s32 D_80085F98[4]; /* forced hi/lo access via size > 8 */

extern s32 EnterCriticalSection(void);
extern s32 ExitCriticalSection(void);
extern void StopRCnt(s32 a0);

/* Sets the D_800737C0 busy/lock flag, enters a critical section, invokes
 * the RCnt-mask-clear helper StopRCnt() on hardware timer 2
 * (0xF2000002), leaves the critical section, then clears the
 * D_80085F98 mode flag and the D_800737C0 lock flag. */
void func_800586B0(void)
{
    D_800737C0.v = 1;
    EnterCriticalSection();
    StopRCnt(0xF2000002);
    ExitCriticalSection();
    D_80085F98[0] = 0;
    D_800737C0.v = 0;
}
