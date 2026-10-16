#include "common.h"
#include "m2c_compat.h"

void func_804056F4(void *arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    void *var_a2;
    void *var_t0;

    var_a3 = 0;
    if (arg1 > 0) {
        var_t2 = 0xCAC;
        var_a2 = arg0;
        var_t1 = 0xB5C;
        var_t0 = arg0;
        do {
            temp_v1 = arg0 + var_t2;
            M2C_FIELD(var_t0, s32 *, 0xB08) = (s32) (arg0 + var_t1);
            var_t2 += 0x10;
            M2C_FIELD(var_a2, s32 *, 0xCAC) = (s32) M2C_FIELD((void *)0x8002D690, s32 *, 0);
            var_t1 += 0x10;
            M2C_FIELD(var_a2, s32 *, 0xCB0) = (s32) M2C_FIELD((void *)0x8002D690, s32 *, 4);
            var_t0 += 4;
            M2C_FIELD(var_a2, s32 *, 0xCB4) = (s32) M2C_FIELD((void *)0x8002D690, s32 *, 8);
            var_a3 += 1;
            M2C_FIELD(var_a2, s32 *, 0xB60) = temp_v1;
            M2C_FIELD(var_a2, s32 *, 0xB64) = (s32) (arg0 + 0xAEC);
            M2C_FIELD(var_a2, s32 *, 0xCB8) = (s32) M2C_FIELD((void *)0x8002D690, s32 *, 0xC);
            var_a2 += 0x10;
        } while (var_a3 < arg1);
    }
    M2C_FIELD(arg0, s32 *, 0xAEC) = (s32) *(s32 *)0x8002D6A0;
    M2C_FIELD(arg0, s32 *, 0xAF0) = (s32) *(s32 *)0x8002D6A4;
    M2C_FIELD(arg0, s32 *, 0xAF4) = (s32) *(s32 *)0x8002D6A8;
}
