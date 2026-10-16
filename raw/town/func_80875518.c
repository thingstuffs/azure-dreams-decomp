#include "common.h"
#include "m2c_compat.h"

s32 func_80700C9C(M2C_UNK);                         /* extern */
M2C_UNK func_80700D24(M2C_UNK);                     /* extern */
M2C_UNK func_80700D54(M2C_UNK);                     /* extern */
s32 func_8070168C();                                /* extern */
extern void *D_80701968;
extern void *D_80701988;

s32 func_80701518(s32 arg0) {
    if ((func_80700C9C(2) != 0) && (*M2C_FIELD(D_80701988, s32 **, 8) > 0)) {
        func_80700D24(2);
        M2C_FIELD(D_80701968, s32 *, 0x34) = (s32) (M2C_FIELD(D_80701968, s32 *, 0x34) | 8);
        return func_8070168C();
    }
    func_80700D54(2);
    return arg0;
}
