#include "common.h"

/* D_800737C0: "in-progress" guard flag for the RCnt/event init sequence.
 * hi/lo access (lui/lw with %hi/%lo, not gp_rel) -> size must be > 8 bytes. */
extern s32 D_800737C0[4];
/* D_80085F9C: stores the event handle returned by OpenEvent. */
extern s32 D_80085F9C[4];
/* D_80085F98: mode/status flag, cleared at the end of the init sequence. */
extern s32 D_80085F98[4];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern s32 OpenEvent(u32 class, s32 spec, s32 mode, void (*func)(void));
extern s32 EnableEvent(s32 event);
extern s32 SetRCnt(u32 spec, u16 target, s32 mode);
extern s32 StartRCnt(u32 spec);

extern void func_80058510(void);

/* If the guard flag D_800737C0 is clear, run the one-time RCnt/event setup:
 * sets the guard, opens+enables an interrupt-mode event bound to
 * func_80058510 on counter 0xF2000002, configures and starts that RCnt,
 * then clears the mode flag and the guard flag again. */
void func_800585A0(void)
{
    if (D_800737C0[0] == 0) {
        D_800737C0[0] = 1;
        EnterCriticalSection();
        D_80085F9C[0] = OpenEvent(0xF2000002, 2, 0x1000, func_80058510);
        EnableEvent(D_80085F9C[0]);
        SetRCnt(0xF2000002, 0x1C00, 0x1000);
        StartRCnt(0xF2000002);
        ExitCriticalSection();
        D_80085F98[0] = 0;
        D_800737C0[0] = 0;
    }
}
