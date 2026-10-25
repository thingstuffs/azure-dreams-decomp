#include "script_symbols.h"
#include "common.h"

void set_selected_entry_state_3(void);                            /* extern */
void func_800193E0(s32);                     /* extern */
extern s32 scene_dispatch_mode_index;

/* Set state 1, invoke handler 0x632, and run the follow-up handler. */
void set_state_one_and_dispatch_632(void) {
    scene_dispatch_mode_index = 1;
    func_800193E0(F_sbs14_pad14);
    set_selected_entry_state_3();
}
