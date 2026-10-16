#include "common.h"
#include "m2c_compat.h"

s32 func_80018FC8(M2C_UNK *, M2C_UNK *, s32, s32);  /* extern */
extern M2C_UNK D_8001673C;
extern M2C_UNK D_80016754;
extern M2C_UNK D_800170CC;
extern s32 D_80019BB4;

s32 func_80017CC0(s32 arg0, s32 arg2) {
    if (arg2 != 1) {
        return func_80018FC8(&D_8001673C, &D_800170CC, arg0, arg2);
    }
    return *((D_80019BB4 * 4) + &D_80016754);
}
