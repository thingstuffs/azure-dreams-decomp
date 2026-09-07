#include "common.h"

extern s32 D_80079954[3];
extern s32 D_80079950[3];
extern s32 D_80079990[3];
extern s32 D_80079994[4];
extern s32 D_800794EC[3];
extern s32 D_800794F0[3];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void func_8005D798(s32 arg0);
extern s32 CloseEvent(s32 event);
extern s32 DisableEvent(s32 event);

/* Shuts down SPU event/callback state when the SPU service flag is active. */
void func_8005D7BC(void)
{
    if (D_80079954[0] == 1) {
        D_80079950[1] = 0;
        EnterCriticalSection();
        {
            register s32 arg0 ASM_REG("$4") = 0;

            D_80079990[0] = 0;
            D_80079994[0] = 0;
            func_8005D798(arg0);
        }
        CloseEvent(D_800794EC[0]);
        DisableEvent(D_800794F0[-1]);
        ExitCriticalSection();
    }
}
