#include "script_symbols.h"
#include "common.h"
void func_80018C74(s32);                     /* extern */
void func_80018CEC(s32);                     /* extern */

/* Invoke the setup handlers with four fixed identifiers. */
s32 invoke_event_setup_handlers(void) {
    func_80018C74(F_s24_door_open);
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    func_80018CEC(F_cheriru_first_nadia2);
    return 0;
}
