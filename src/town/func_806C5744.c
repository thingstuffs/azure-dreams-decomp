#include "common.h"
void func_80018C74(s32);                     /* extern */
void func_80018CEC(s32);                     /* extern */

/* Invoke the setup handlers with four fixed identifiers. */
s32 invoke_event_setup_handlers(void) {
    func_80018C74(0x1463);
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    func_80018CEC(0xFDB);
    return 0;
}
