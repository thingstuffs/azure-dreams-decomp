#include "common.h"

extern s32 D_80079950[3];
extern s32 D_80079954[];
extern s32 D_800794EC[];

extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void func_8005D064(void);
extern void func_8005D798(void (*arg0)(void));
extern s32 OpenEvent(u32 class, s32 spec, s32 mode, void (*func)(void));
extern s32 EnableEvent(s32 event);

/* Starts the SPU callback/event service once when it is not already active. */
void func_8005CB88(void)
{
    s32 event_handle;

    if (D_80079950[1] == 0) {
        D_80079954[0] = 1;
        EnterCriticalSection();
        func_8005D798(func_8005D064);
        event_handle = OpenEvent(0xF0000009, 0x20, 0x2000, 0);
        D_800794EC[0] = event_handle;
        EnableEvent(event_handle);
        ExitCriticalSection();
    }
}
