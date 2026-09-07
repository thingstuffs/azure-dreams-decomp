#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017724();                     /* extern */
s32 func_80017948();                         /* extern */
s32 func_80017990();                         /* extern */
extern M2C_UNK D_80017AB8;
extern M2C_UNK *D_80017B6C;

void func_80761DA4(void) {
    D_80017B6C = &D_80017AB8;
    if (func_80017948(7) != 0) {
        func_80017724(0x9DE);
    }
    if (func_80017990(7) != 0) {
        func_80017724(0x9DD);
    }
}
