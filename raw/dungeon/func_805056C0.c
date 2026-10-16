#include "common.h"
#include "m2c_compat.h"

s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_8001CEC0(void *arg0) {
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 var_v0;
    u16 var_a1;
    u16 var_a2;
    void *temp_v1;

    temp_t0 = func_800A6D30() & 1;
    var_a2 = M2C_FIELD(arg0, u16 *, 2);
    temp_t1 = M2C_FIELD(arg0, u16 *, 0) + M2C_FIELD(arg0, u16 *, 4);
    temp_t2 = var_a2 + M2C_FIELD(arg0, u16 *, 6);
    if ((s32) var_a2 < temp_t2) {
        do {
            var_a1 = M2C_FIELD(arg0, u16 *, 0);
            var_v0 = var_a1 & 1;
            if ((s32) var_a1 < temp_t1) {
                do {
                    if ((var_v0 == temp_t0) && ((var_a2 & 1) == temp_t0)) {
                        temp_v1 = (((var_a2 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_a1) * 6) + &D_800EA000;
                        M2C_FIELD(temp_v1, s16 *, 0) = (s16) (((u16) M2C_FIELD(temp_v1, u16 *, 4) >> 1) + 0x63);
                        M2C_FIELD(temp_v1, u16 *, 4) = (u16) (M2C_FIELD(temp_v1, u16 *, 4) | 0x8000);
                        M2C_FIELD(temp_v1, u16 *, 2) = (u16) (M2C_FIELD(temp_v1, u16 *, 2) - 0x60);
                    }
                    var_a1 += 1;
                    var_v0 = var_a1 & 1;
                } while ((s32) var_a1 < temp_t1);
            }
            var_a2 += 1;
        } while ((s32) var_a2 < temp_t2);
    }
}
