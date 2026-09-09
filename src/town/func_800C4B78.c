#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024100(); /* extern */
M2C_UNK func_800C22A4();                            /* extern */

/* start_mogura_func: initialize the mogura activity and reset its four control values. */
void start_mogura_func(void) {
    func_800C22A4();
    func_80024100(0, 0, 0, 0);
}
