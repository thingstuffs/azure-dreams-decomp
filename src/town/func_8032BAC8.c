#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001ACE8();                     /* extern */

/* Process IDs 0x1462, 0x1474, and 0xD89 in sequence. */
void func_800162C8(void) {
    func_8001ACE8(0x1462);
    func_8001ACE8(0x1474);
    func_8001ACE8(0xD89);
}
