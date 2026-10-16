#include "common.h"
#include "m2c_compat.h"

void func_80157284(void *arg0, void *arg1, void *arg2) {
    s32 var_a2;
    s32 var_v1;
    u8 temp_t0;
    void *temp_v1;
    void *var_a1;

    M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s32 *, 8);
    M2C_FIELD(arg2, s16 *, 0x14) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), u16 *, 0x14) | 0xC);
    temp_t0 = M2C_FIELD(arg0, u8 *, 0x17);
    if (temp_t0 == 0) {
        if ((s32) M2C_FIELD(arg2, u8 *, 0xC) < (0x80 >> M2C_FIELD(arg0, s16 *, 0x34))) {
            var_v1 = 0x101010;
            goto block_6;
        }
        M2C_FIELD(arg0, u8 *, 0x17) = (u8) (temp_t0 + 1);
    } else if (M2C_FIELD(arg2, u8 *, 0xC) != 0) {
        var_v1 = 0xFFF7F7F8;
block_6:
        M2C_FIELD(arg2, u8 *, 0xC) = (s32) ((s32) M2C_FIELD(arg2, u8 *, 0xC) + var_v1);
    } else {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0x20);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0x26);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    var_a2 = 0;
    if (M2C_FIELD(arg0, s16 *, 0x34) > 0) {
        var_a1 = arg0;
        do {
            var_a2 += 1;
            M2C_FIELD(var_a1, u16 *, 0x20) = (u16) M2C_FIELD(var_a1, u16 *, 0x22);
            M2C_FIELD(var_a1, u16 *, 0x26) = (u16) M2C_FIELD(var_a1, u16 *, 0x28);
            M2C_FIELD(var_a1, u16 *, 0x2C) = (u16) M2C_FIELD(var_a1, u16 *, 0x2E);
            var_a1 += 2;
        } while (var_a2 < M2C_FIELD(arg0, s16 *, 0x34));
    }
    temp_v1 = (var_a2 * 2) + arg0;
    M2C_FIELD(temp_v1, u16 *, 0x20) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 2);
    M2C_FIELD(temp_v1, u16 *, 0x26) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 6);
    M2C_FIELD(temp_v1, u16 *, 0x2C) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 0xA);
}
