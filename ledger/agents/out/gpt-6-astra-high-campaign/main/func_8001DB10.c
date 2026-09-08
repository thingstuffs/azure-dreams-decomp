#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804047B0();                         /* extern */
M2C_UNK func_80404818();                         /* extern */
M2C_UNK func_80404888();                         /* extern */
M2C_UNK func_804048F8();                         /* extern */
M2C_UNK func_80404A3C();                         /* extern */

/* Process four embedded components, then the containing object. */
void func_8001DB10(s32 object_addr) {
    func_804047B0(object_addr + 8);
    func_80404818(object_addr + 0x80);
    func_80404888(object_addr + 0xF8);
    func_80404A3C(object_addr + 0x170);
    func_804048F8(object_addr);
}
