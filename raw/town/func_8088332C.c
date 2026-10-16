#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700894(M2C_UNK);                     /* extern */
s32 func_80700A78();                                /* extern */
M2C_UNK func_80700AD4();                            /* extern */
M2C_UNK func_80700D48(s32, s32);                    /* extern */

s32 func_80700B2C(void) {
    s32 temp_v0;

    func_80700894(0);
    func_80700AD4();
    temp_v0 = func_80700A78();
    *(s32 *)0x8070070C = temp_v0;
    func_80700D48(temp_v0, *(s32 *)0x80700710);
    return *(void *)0x8070070C;
}
