#include "common.h"
void func_80018CEC(s32);                     /* extern */

/* Call func_80018CEC with IDs 0xFCB and 0xFCD, then return zero. */
s32 update_flag_0x511_from_selection(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
