#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804047B0();                         /* extern */
M2C_UNK func_80404818();                         /* extern */
M2C_UNK func_80404888();                         /* extern */
M2C_UNK func_804048F8();                         /* extern */
M2C_UNK func_80404A3C();                         /* extern */

void func_8001DB10(s32 arg0) {
    func_804047B0(arg0 + 8);
    func_80404818(arg0 + 0x80);
    func_80404888(arg0 + 0xF8);
    func_80404A3C(arg0 + 0x170);
    func_804048F8(arg0);
}
