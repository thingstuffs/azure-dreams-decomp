#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003500C(M2C_UNK *);                   /* extern */
M2C_UNK func_800472D4(void *, u8, s8);              /* extern */
M2C_UNK func_80047454(void *);                      /* extern */
M2C_UNK func_8009EFFC(s32, void *);                 /* extern */
s32 func_800A8B28(void *, void *, void *, void *);  /* extern */
M2C_UNK func_800A9024(void *, void *, void *, void *); /* extern */
s16 func_800BB784(s32, s32, s16);                   /* extern */
extern M2C_UNK D_8014C514;
extern M2C_UNK D_8014EEF4;
extern M2C_UNK D_8014EFC8;

void func_8014C12C(void *arg0, void *arg1, void *arg2) {
    M2C_UNK (*temp_v0_2)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1_2)(void *, void *, void *, void *);
    s16 temp_a1;
    s16 temp_s1_2;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s32 temp_a0;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_s1;
    void *temp_v0;
    void *temp_v1;
    void *var_a0;

    if ((M2C_FIELD(arg0, u8 *, 0xBB) == 0) && (*(s16 *)0x8008599A == 0)) {
        M2C_FIELD(arg0, u8 *, 0xBB) = 1U;
        func_8003500C(&D_8014EFC8);
        M2C_FIELD(arg0, u8 *, 0x6D) = 0U;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    }
    if (*(u16 *)0x80013714 & 8) {
        var_a1 = 1;
        var_a0 = *(s32 *)0x800E397C + 4;
        do {
            temp_v0 = M2C_FIELD(var_a0, void **, 0xAC);
            if (temp_v0 != NULL) {
                temp_v1 = M2C_FIELD(temp_v0, void **, -0x14);
                M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) & 0xFFBF);
            }
            var_a1 -= 1;
            var_a0 -= 4;
        } while (var_a1 >= 0);
    }
    if (*(u16 *)0x80085992 & 0x2000) {
        temp_v1_2 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1_2 == &D_8014C514) {
            temp_v1_2(arg0, arg1, arg2, arg0);
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
        return;
    }
    temp_s1 = (s8) M2C_FIELD(arg0, u8 *, 0x6D);
    if (func_800A8B28(arg0, arg1, arg2, arg0) == 0) {
        temp_v0_2 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0_2 != NULL) {
            temp_v0_2(arg0, arg1, arg2, arg0);
        }
        *((M2C_FIELD(arg0, u8 *, 0x9A) * 4) + &D_8014EEF4)(arg0, arg1, arg2, arg0);
        if ((s16) temp_s1 != (s8) M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800A9024(arg0, arg1, arg2, arg0);
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        temp_s1_2 = ((s32) (*(s16 *)0x800848E0 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7;
        if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s1_2) {
            func_800472D4(arg2, *(M2C_FIELD(arg2, s32 *, 0x2C) + temp_s1_2), M2C_FIELD(arg2, s8 *, 4));
            M2C_FIELD(arg0, s16 *, 0x94) = temp_s1_2;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
        func_8009EFFC(M2C_FIELD(arg0, s32 *, 0x1C), arg2 + 0xC);
        if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x20)) {
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                func_80047454(arg2);
            }
        } else {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xFFFBFFFF);
        }
        if (M2C_FIELD(arg0, s16 *, 0xB8) == 1) {
            temp_a1 = M2C_FIELD(arg1, s16 *, 0x16);
            temp_v1_3 = M2C_FIELD(arg1, s16 *, 0xA);
            var_v0 = temp_a1 - temp_v1_3;
            if (temp_v1_3 < temp_a1) {
                if (var_v0 < 0) {
                    var_v0 = -var_v0;
                }
                if (var_v0 >= 0x65) {
                    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + 8);
                } else {
                    temp_a0 = M2C_FIELD(arg1, s32 *, 8);
                    var_v0_2 = M2C_FIELD(arg1, s32 *, 0x14) - temp_a0;
                    if (var_v0_2 < 0) {
                        var_v0_2 = -var_v0_2;
                    }
                    M2C_FIELD(arg1, s32 *, 8) = (s32) (temp_a0 + (var_v0_2 / 10));
                }
            }
        }
        if ((M2C_FIELD(arg0, s16 *, 0xB8) == 2) && (M2C_FIELD(arg1, s16 *, 0xA) >= -0x3EF)) {
            M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4);
        }
        temp_v1_4 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_v1_4 & 0x40000000) {
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v1_4 & 0xBFFFFFFF);
            temp_v0_3 = func_800BB784((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20));
            if (temp_v0_3 < 0x200) {
                M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + (M2C_FIELD(arg0, u16 *, 0x88) - temp_v0_3));
                M2C_FIELD(arg0, u16 *, 0x88) = (u16) temp_v0_3;
            }
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
}
