#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_800892E4[];
s32 func_8004491C();
extern s32 D_80044C54;
extern s32 D_800814A0[];

void func_800B490C(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 temp_v1;
    s16 var_v0;
    s32 var_v0_3;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, void **, 0);
    if (temp_v0 == NULL) {
        goto block_3;
    }
    if (!(M2C_FIELD(temp_v0, u16 *, 0x1E) & 0x8000)) {
        goto block_3;
    }
    M2C_FIELD(arg0, void **, 0) = NULL;
    M2C_FIELD(arg0, void **, 0x14) = NULL;
block_3:
    if (M2C_FIELD(arg0, s16 *, 0x10) == 0) {
        goto block_5;
    }
    M2C_FIELD(arg0, s16 *, 0x10) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x10) - 1);
    return;
block_5:
    temp_v0_2 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_v0_2 == NULL) {
        goto block_7;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) - (M2C_FIELD(arg0, u16 *, 0x18) - M2C_FIELD(temp_v0_2, u16 *, 2)));
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) - (M2C_FIELD(arg0, u16 *, 0x1A) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 6)));
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 6);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - (M2C_FIELD(arg0, u16 *, 0x1C) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 0xA)));
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 0xA);
block_7:
    temp_v1 = M2C_FIELD(arg0, s16 *, 8);
    if ((u32) temp_v1 >= 5U) {
        goto block_19;
    }
    (void)jt_keep; goto *D_800892E4[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg1, s32 *, 0x14) = 0x200000;
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80);
    M2C_FIELD(arg0, s32 *, 4) = 0x200000;
    M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    func_8004491C(arg0 - 0x20, &D_80044C54);
    M2C_FIELD(arg0, u16 *, 0xA) = 0x10U;
    M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + 1);
jt_c1:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_3;
    if ((s16) temp_v0_3 <= 0) {
        goto block_12;
    }
    temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xE);
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / (s16) temp_v0_3);
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_3;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_3;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_3;
    goto block_19;
block_12:
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 8) + 1;
    goto block_15;
jt_c3:
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_19;
    }
    var_v1 = 8;
    M2C_FIELD(arg0, u16 *, 0xA) = var_v1;
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 8) + 1;
block_15:
    M2C_FIELD(arg0, s16 *, 8) = var_v0;
    goto block_19;
jt_c4:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_5;
    if ((s16) temp_v0_5 <= 0) {
        goto block_18;
    }
    temp_v1_4 = M2C_FIELD(arg2, u16 *, 0x1E);
    temp_v1_5 = temp_v1_4 + ((s32) (0 - temp_v1_4) / (s16) temp_v0_5);
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v1_5;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v1_5;
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + 6);
    goto block_19;
block_18:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] |= 0x8000;
jt_c2:
block_19:
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0xC) + 1;
    M2C_FIELD(arg0, u16 *, 0xC) = temp_v0_6;
    if (!(temp_v0_6 & 1)) {
        goto block_28;
    }
    temp_v0_7 = M2C_FIELD(arg1, s32 *, 0x14);
    var_v1 = temp_v0_7 >> 1;
    var_v0_2 = temp_v0_7 >> 0x11;
    if (var_v0_2 >= 0) {
        goto block_22;
    }
    var_v0_2 = 0 - var_v0_2;
block_22:
    M2C_FIELD(arg1, s32 *, 0x14) = var_v1;
    if (var_v0_2 >= 2) {
        goto block_28;
    }
    temp_v0_8 = 0 - ((s32) M2C_FIELD(arg0, s32 *, 4) >> 1);
    M2C_FIELD(arg0, s32 *, 4) = temp_v0_8;
    M2C_FIELD(arg1, s32 *, 0x14) = temp_v0_8;
    var_v0_3 = M2C_FIELD(arg0, s16 *, 6);
    if (var_v0_3 >= 0) {
        goto block_25;
    }
    var_v0_3 = 0 - var_v0_3;
block_25:
    if (var_v0_3 >= 2) {
        goto block_28;
    }
    if (M2C_FIELD(arg0, s16 *, 8) >= 3) {
        goto block_28;
    }
    M2C_FIELD(arg0, s16 *, 8) = 3;
    M2C_FIELD(arg0, u16 *, 0xA) = 8U;
block_28:
    if (M2C_FIELD(arg0, s16 *, 0xE) == 0) {
        goto block_32;
    }
    var_v1 = 0x2CF0F0F0;
    if (!(M2C_FIELD(arg0, u16 *, 0xC) & 3)) {
        goto block_31;
    }
    var_v1 = 0x2C404040;
block_31:
    M2C_FIELD(arg2, s32 *, 0xC) = var_v1;
block_32:
    return;
}
