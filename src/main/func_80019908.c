#include "common.h"

s32 wait_selected();                         /* extern */
void invoke_callback_for_four_global_values();                            /* extern */
void func_80408654(s32);                     /* extern */

/* Run setup for both indices and apply the stored value. */
void func_80019908(void) {
    invoke_callback_for_four_global_values();
    func_80408654(0);
    func_80408654(1);
    wait_selected(*(s32 *)0x804094EC);
}
