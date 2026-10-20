#include "shared/runtime_dispatch.h"
#include "common.h"

extern s8 D_80080A84[];
extern s8 D_80080A88[];


extern void card_boot_close_events(void);
extern void open_timer_2_update_event(void);
extern void SD_Call(s32 flags);

/* Set state 2, run setup, select sound behavior, and clear the high flag bit. */
void card_boot_close_events_and_resume_timer(void) {
    D_80080A84[0] = 2;
    card_boot_close_events();
    open_timer_2_update_event();
    if (D_80082E60.mode == 1) {
        SD_Call(0x200);
    } else {
        D_80080A88[0] = 0;
    }
    D_80082E60.flags0F &= 0x7F;
}
