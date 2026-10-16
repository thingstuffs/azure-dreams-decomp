#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800AAA54(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8015F400;
extern M2C_UNK D_80163148;
extern M2C_UNK D_80163158;

void func_80161354(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_v0_2;
    s16 var_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s3 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 9) & 7;
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800AD4D0(arg3);
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
block_24:
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80163158);
            return;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
            return;
        }
        temp_v1_2 = temp_s3 * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_v1_2 + &D_8006CCD8) << 0x12);
        M2C_FIELD(arg1, s32 *, 0x14) = 0x40000;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_v1_2 + &D_8006CCE8) << 0x12);
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF & 0xFFFBFFFF);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        var_v1 = -1;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x228) {
            var_v1 = 8;
        }
        M2C_FIELD(arg0, s16 *, 0x96) = var_v1;
        temp_v1_3 = M2C_FIELD(arg1, s32 *, 0xC);
        var_v0 = temp_v1_3;
        if (temp_v1_3 < 0) {
            var_v0 = temp_v1_3 + 3;
        }
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1_3 - (var_v0 >> 2));
        var_v0_2 = temp_a0;
        if (temp_a0 < 0) {
            var_v0_2 = temp_a0 + 3;
        }
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a0 - (var_v0_2 >> 2));
        return;
    case 1:
        temp_a0_2 = temp_s3 * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) - (*(temp_a0_2 + &D_8006CCD8) << 0xE));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) - (*(temp_a0_2 + &D_8006CCE8) << 0xE));
        if (M2C_FIELD(arg0, s16 *, 0x96) > 0) {
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x96) - 1);
        } else if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
        }
        if (M2C_FIELD(arg0, s16 *, 0x96) == 0) {
            if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
                M2C_FIELD(arg0, u8 *, 0x9B) = 0U;
                goto block_24;
            }
            M2C_FIELD(arg0, s16 *, 0x96) = 8;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 2:
        M2C_FIELD(arg1, s32 *, 0x14) = 0xFFFE0000;
        if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0xF) >> 1);
            temp_v1_4 = M2C_FIELD(arg1, s32 *, 0xC);
            temp_v0 = (s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0xF) >> 1;
            M2C_FIELD(arg1, s32 *, 0x10) = temp_v0;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1_4 + (temp_v1_4 >> 1));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v0 + (temp_v0 >> 1));
        }
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000 | 0x40000);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80163148;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80163148), 0);
            if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
            }
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015F400;
        }
        break;
    }
}
