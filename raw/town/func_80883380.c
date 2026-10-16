#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700804(M2C_UNK);                     /* extern */
M2C_UNK func_80700894(M2C_UNK);                     /* extern */
M2C_UNK func_80700998(s32, M2C_UNK);                /* extern */

s32 func_80700B80(void) {
    s32 temp_a0;
    s32 temp_s0;

    func_80700894(1);
    temp_a0 = *(s32 *)0x8070070C;
    temp_s0 = M2C_FIELD(((temp_a0 * 0x10) + 0x80700000), s32 *, 0x738);
    func_80700998(temp_a0, 1);
    func_80700804(1);
    return temp_s0;
}
