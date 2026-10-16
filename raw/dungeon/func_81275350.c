#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, void *, s16);        /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, void *, void *); /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8014C898;
extern M2C_UNK D_8014FEB4;

void func_8014CB50(void *arg0, void *arg1, void *arg2, s16 arg3) {
    u16 temp_v0_2;
    void *temp_a1;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *var_a2;
    void *var_a3;

    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8014C898;
        M2C_FIELD(temp_s2, s16 *, 0xB6) = arg3;
        M2C_FIELD(temp_s2, s32 *, 0xAC) = (s32) (arg0 - 0x20);
        M2C_FIELD(temp_s2, u16 *, 0x94) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        var_a3 = arg2;
        M2C_FIELD(temp_s2, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        var_a2 = temp_s1;
        do {
            M2C_FIELD(var_a2, s32 *, 0) = (s32) M2C_FIELD(var_a3, s32 *, 0);
            M2C_FIELD(var_a2, s32 *, 4) = (s32) M2C_FIELD(var_a3, s32 *, 4);
            M2C_FIELD(var_a2, s32 *, 8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
            M2C_FIELD(var_a2, s32 *, 0xC) = (s32) M2C_FIELD(var_a3, s32 *, 0xC);
            var_a3 += 0x10;
            var_a2 += 0x10;
        } while (var_a3 != (arg2 + 0x30));
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        M2C_FIELD(temp_s1, M2C_UNK **, 0x2C) = &D_8014FEB4;
        func_80047784(temp_s1, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg0, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8014FEB4), 0);
        M2C_FIELD(temp_s1, s16 *, 0x10) = 0x20;
        temp_v0_2 = M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_s1, u16 *, 0x14) = temp_v0_2;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (temp_v0_2 | 0x80);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        temp_a1 = M2C_FIELD(arg0, void **, -0x14);
        if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, temp_s2 + 0xB0, arg3) != 0) {
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + M2C_FIELD(temp_s2, u16 *, 0xB0));
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + M2C_FIELD(temp_s2, u16 *, 0xB2));
            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) + M2C_FIELD(temp_s2, u16 *, 0xB4));
        }
        M2C_FIELD(temp_s1, u16 *, 0x1C) = (u16) M2C_FIELD(arg2, u16 *, 0x1C);
        M2C_FIELD(temp_s1, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s1, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s1, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s1, u16 *, 0x1E) = (u16) M2C_FIELD(arg2, u16 *, 0x1E);
    }
}
