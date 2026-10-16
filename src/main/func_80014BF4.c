#include "shared/runtime_dispatch.h"
#include "common.h"

extern s8 D_80080A84[];
extern s8 D_80080A88[];


extern void cardBootCloseEvents(void);
extern void openTimer2UpdateEvent(void);
extern void SD_Call(s32 flags);

/* Set state 2, run setup, select sound behavior, and clear the high flag bit. */
void cardBootCloseEventsAndResumeTimer(void) {
    D_80080A84[0] = 2;
    cardBootCloseEvents();
    openTimer2UpdateEvent();
    if (D_80082E60.mode == 1) {
        SD_Call(0x200);
    } else {
        D_80080A88[0] = 0;
    }
    D_80082E60.flags0F &= 0x7F;
}
