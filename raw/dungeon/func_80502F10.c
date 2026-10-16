#include "common.h"
#include "m2c_compat.h"

extern s32 D_8001F660;
extern u8 D_8001F6A0;
extern M2C_UNK D_8001F6A4;
extern M2C_UNK D_8001F6E8;

void func_8001A710(void) {
    s32 var_a1;
    void *temp_v0;

    M2C_FIELD(&D_8001F6A4, s8 *, 3) = 0;
    M2C_FIELD(&D_8001F6A4, s8 *, 2) = 0;
    M2C_FIELD(&D_8001F6A4, s8 *, 1) = 0;
    M2C_FIELD(&D_8001F6A4, s8 *, 0) = 0;
    var_a1 = D_8001F660 - 1;
    D_8001F6A0 = (u8) D_8001F660;
    if (var_a1 >= 0) {
        do {
            temp_v0 = var_a1 + &D_8001F6E8;
            var_a1 -= 1;
            M2C_FIELD(temp_v0, s8 *, 0) = 0;
            M2C_FIELD(temp_v0, s8 *, 4) = 0;
        } while (var_a1 >= 0);
    }
}
