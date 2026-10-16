#include "common.h"
#include "m2c_compat.h"

s32 func_8070021C(M2C_UNK);                         /* extern */
M2C_UNK func_807002A4(M2C_UNK);                     /* extern */
M2C_UNK func_807002D4(M2C_UNK);                     /* extern */
s32 func_80700B7C();                                /* extern */

s32 func_80700A20(s32 arg0) {
    void *temp_v1;

    if ((func_8070021C(2) != 0) && (*M2C_FIELD(*(void **)0xA0700F5C, s32 **, 8) > 0)) {
        func_807002A4(2);
        temp_v1 = *(void **)0xA0700F40;
        M2C_FIELD(temp_v1, u8 *, 0xE) = (u8) M2C_FIELD(temp_v1, u8 *, 0xE);
        return func_80700B7C();
    }
    func_807002D4(2);
    return arg0;
}
