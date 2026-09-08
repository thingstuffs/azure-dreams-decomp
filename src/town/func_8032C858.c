#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800188B8();                            /* extern */
M2C_UNK func_8001ACE8();                     /* extern */

/* Runs func_8001ACE8 with code 0x1452 and its func_800188B8 follow-up. */
void func_80017058(void) {
    func_8001ACE8(0x1452);
    func_800188B8();
}
