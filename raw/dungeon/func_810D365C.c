#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800AAA54(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8014CE54;
extern M2C_UNK D_8014FC94;

void func_8014EE5C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_s3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a0;
    u16 var_v1;
    u8 temp_v1;
    u8 var_v0_3;

    temp_a0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    temp_s3 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 9) & 7;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = temp_a0;
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800AD4D0(arg3);
        M2C_FIELD(arg0, u16 *, 0x96) = 2U;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            func_800AAA54(arg0, arg1, arg2, &D_8014FC94);
            return;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            return;
        }
    case 1:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            temp_v1_2 = temp_s3 * 2;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_v1_2 + &D_8006CCD8) << 0x12);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_v1_2 + &D_8006CCE8) << 0x12);
            var_v1 = 5;
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x228) {
                var_v1 = 8;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = var_v1;
            temp_v1_3 = M2C_FIELD(arg1, s32 *, 0xC);
            var_v0 = temp_v1_3;
            if (temp_v1_3 < 0) {
                var_v0 = temp_v1_3 + 3;
            }
            temp_a0_2 = M2C_FIELD(arg1, s32 *, 0x10);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1_3 - (var_v0 >> 2));
            var_v0_2 = temp_a0_2;
            if (temp_a0_2 < 0) {
                var_v0_2 = temp_a0_2 + 3;
            }
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a0_2 - (var_v0_2 >> 2));
            var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_23:
            M2C_FIELD(arg0, u8 *, 0x9B) = var_v0_3;
            return;
        }
        return;
    case 2:
        temp_a0_3 = temp_s3 * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) - (*(temp_a0_3 + &D_8006CCD8) << 0xF));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) - (*(temp_a0_3 + &D_8006CCE8) << 0xF));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0) {
            if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                func_800AAA54(arg0, arg1, arg2, &D_8014FC94);
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_23;
        }
        break;
    case 3:
        if (((temp_a0 << 0x10) == 0) || (M2C_FIELD(arg1, s32 *, 0xC) = (s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0xF), M2C_FIELD(arg1, s32 *, 0x10) = (s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0xF), ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0))) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
            }
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014CE54;
        }
        break;
    }
}
