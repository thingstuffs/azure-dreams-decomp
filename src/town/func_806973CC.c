#include "common.h"

typedef s32 M2C_UNK;

void func_80016450(void) __attribute__((noreturn));
s32 func_80017B24();
M2C_UNK *func_80017BDC();
M2C_UNK func_8001856C();
s32 func_800187D8();
extern M2C_UNK D_80018974;
extern M2C_UNK D_80018AD0;
extern M2C_UNK D_80019F15;
extern M2C_UNK D_8001A0A1;

M2C_UNK *func_806973CC(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK *temp_s3;
    M2C_UNK *var_v0;

    temp_s3 = func_80017BDC(&D_80018974, &D_80018AD0, arg0, arg2);
    var_v0 = temp_s3;
    if (func_80017B24(&D_80018974, arg0, arg2) != 0) {
        if (func_800187D8(8) != 0) {
#ifndef NON_MATCHING
            var_v0 = &D_8001A0A1;
#else
            var_v0 = &D_8001A0A1;
#endif
            ASM_TAILSLOT_PIN(var_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80016450();
            var_v0 = &D_8001A0A1;
        } else {
            func_8001856C(0x12C8);
            var_v0 = &D_80019F15;
        }
    }
    return var_v0;
}
