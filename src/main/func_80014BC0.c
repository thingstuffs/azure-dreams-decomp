#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8006A084();                            /* extern */
M2C_UNK func_8006A094();                            /* extern */
M2C_UNK func_8006A248();                     /* extern */

/* Bracket command 0xF2000002 with setup and completion calls. */
void cardBootStartHardwareCounter(void) {
    func_8006A084();
    func_8006A248(0xF2000002);
    func_8006A094();
}
