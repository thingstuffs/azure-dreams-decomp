#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8007CA38();                            /* extern */
M2C_UNK func_8007CA48();                            /* extern */
M2C_UNK func_8007CB08();                     /* extern */
M2C_UNK func_804087A8();                            /* extern */

void func_802F1730(void) {
    func_8007CA38();
    func_804087A8();
    func_8007CB08(0);
    func_8007CA48();
}
