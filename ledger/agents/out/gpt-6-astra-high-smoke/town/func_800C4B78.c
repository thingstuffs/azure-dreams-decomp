#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024100(); /* extern */
M2C_UNK func_800C22A4();                            /* extern */

/* Implements start_mogura_func by initializing the event and calling func_80024100 with zeros. */
void func_800C22D8(void) {
    func_800C22A4();
    func_80024100(0, 0, 0, 0);
}
