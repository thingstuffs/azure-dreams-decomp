#include "common.h"

void set_selected_entry_state_3();                            /* extern */
void func_800193E0(s32);                     /* extern */
extern s32 D_8001967C;

/* Set state 1, invoke handler 0x632, and run the follow-up handler. */
void set_state_one_and_dispatch_632(void) {
    D_8001967C = 1;
    func_800193E0(0x632);
    set_selected_entry_state_3();
}
