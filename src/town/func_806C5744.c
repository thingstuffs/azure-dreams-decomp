#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018C74();                     /* extern */
M2C_UNK func_80018CEC();                     /* extern */

/* Invoke the setup handlers with four fixed identifiers. */
s32 func_80016744(void) {
    func_80018C74(0x1463);
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    func_80018CEC(0xFDB);
    return 0;
}
