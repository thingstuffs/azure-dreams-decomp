#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047738(void *, u8, s8);              /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
M2C_UNK func_800A020C(s32, void *);                 /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
extern M2C_UNK D_8006CCF8;
extern M2C_UNK D_80170E54;
extern M2C_UNK D_80173A18;

void func_80170A28(void *arg0, void *arg1, void *arg2) {
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    s16 temp_a0;
    s16 temp_s0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v0_2;
    s32 temp_v1_3;
    s8 temp_s0;
    u16 temp_v1_2;
    u16 var_v0;
    u16 var_v0_2;

    if (*(u16 *)0x80083462 & 0x2000) {
        temp_v1 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1 == &D_80170E54) {
            temp_v1(arg0);
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
        return;
    }
    temp_s0 = (s8) M2C_FIELD(arg0, u8 *, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        *((M2C_FIELD(arg0, u8 *, 0x9A) * 4) + &D_80173A18)(arg0, arg1, arg2, arg0);
        if ((s16) temp_s0 != (s8) M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_2 & 0x8000)) {
            temp_s0_2 = ((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7;
            if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0_2) {
                temp_v0_2 = M2C_FIELD(arg2, s32 *, 0x2C);
                if (temp_v0_2 != 0) {
                    func_80047738(arg2, *(temp_v0_2 + temp_s0_2), M2C_FIELD(arg2, s8 *, 4));
                }
                M2C_FIELD(arg0, s16 *, 0x94) = temp_s0_2;
            }
            if (*(temp_s0_2 + &D_8006CCF8) != 0) {
                var_v0 = M2C_FIELD(arg2, u16 *, 0x14) | 1;
            } else {
                var_v0 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0;
            if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
                }
            } else {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
            }
            func_800A020C(M2C_FIELD(arg0, s32 *, 0x1C), arg2 + 0xC);
        } else {
            var_v0_2 = temp_v1_2 & 0x8FFF;
            if (!(temp_v1_2 & 0x800)) {
                var_v0_2 = temp_v1_2 | 0x7000;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0_2;
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        if (M2C_FIELD(arg0, u16 *, 0x98) & 8) {
            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        } else {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, s8 *, 0x9D) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1);
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 4) && (temp_v0_3 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)), ((temp_v0_3 < 0x200) != 0))) {
            temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 0x88);
            if ((M2C_FIELD(arg0, s16 *, 0x92) + temp_a0) < temp_v0_3) {
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF);
            } else if (temp_v0_3 >= temp_a0) {
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
                M2C_FIELD(arg0, s8 *, 0x9D) = 0;
            } else {
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
                M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v0_3 - M2C_FIELD(arg0, u16 *, 0x88));
            }
            temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x1C);
            if (temp_v1_3 & 0x40000000) {
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v1_3 & 0xBFFFFFFF);
                temp_v0_4 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20));
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg0, u16 *, 0x88) - temp_v0_4));
                M2C_FIELD(arg0, u16 *, 0x88) = (u16) temp_v0_4;
            }
        } else {
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF);
        }
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
}
