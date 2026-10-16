#include "common.h"
#include "m2c_compat.h"

s16 func_800C2B38(void *, s32, s32);                /* extern */
s32 func_800C30E0();                                /* extern */
M2C_UNK func_800C95A8(void *, void *, M2C_UNK);     /* extern */
extern M2C_UNK D_800D4FE8;
extern M2C_UNK D_800D4FF8;
extern M2C_UNK D_800D5008;
extern M2C_UNK D_800D5018;

void func_800C9384(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;

    if (func_800C30E0() == 0) {
        temp_a1 = M2C_FIELD(arg1, s32 *, 0xC);
        temp_a2 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + temp_a1);
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a2);
        M2C_FIELD(arg1, s16 *, 0xA) = func_800C2B38(arg1, temp_a1, temp_a2);
        temp_a1_2 = ((s32) (0x400 - M2C_FIELD(arg0, s16 *, 0x72)) / 1024) & 3;
        switch (temp_a1_2) {                        /* irregular */
        case 0:
            if ((M2C_FIELD(arg0, s16 *, 0x84) + M2C_FIELD(arg0, s16 *, 0x8C)) < M2C_FIELD(arg1, s16 *, 2)) {
                M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x84) + (u16) M2C_FIELD(arg0, s16 *, 0x8C));
block_15:
                func_800C95A8(arg0, arg1, arg2);
                return;
            }
block_16:
            temp_a0 = temp_a1_2 * 4;
            var_v1 = M2C_FIELD(arg1, s32 *, 0xC) + *(temp_a0 + &D_800D4FE8);
            M2C_FIELD(arg1, s32 *, 0xC) = var_v1;
            if (var_v1 < 0) {
                var_v1 = -var_v1;
            }
            if (var_v1 > 0x20000) {
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) *(temp_a0 + &D_800D4FF8);
            }
            var_v1_2 = M2C_FIELD(arg1, s32 *, 0x10) + *(temp_a0 + &D_800D5008);
            M2C_FIELD(arg1, s32 *, 0x10) = var_v1_2;
            if (var_v1_2 < 0) {
                var_v1_2 = -var_v1_2;
            }
            if (var_v1_2 > 0x20000) {
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) *(temp_a0 + &D_800D5018);
            }
            break;
        case 1:
            if ((M2C_FIELD(arg0, s16 *, 0x86) + M2C_FIELD(arg0, s16 *, 0x8E)) < M2C_FIELD(arg1, s16 *, 6)) {
                M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x86) + (u16) M2C_FIELD(arg0, s16 *, 0x8E));
                goto block_15;
            }
            goto block_16;
        case 2:
            if (M2C_FIELD(arg1, s16 *, 2) < (M2C_FIELD(arg0, s16 *, 0x84) - M2C_FIELD(arg0, s16 *, 0x8C))) {
                M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x84) - (u16) M2C_FIELD(arg0, s16 *, 0x8C));
                goto block_15;
            }
            goto block_16;
        default:
            if (M2C_FIELD(arg1, s16 *, 6) < (M2C_FIELD(arg0, s16 *, 0x86) - M2C_FIELD(arg0, s16 *, 0x8E))) {
                M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x86) - (u16) M2C_FIELD(arg0, s16 *, 0x8E));
                goto block_15;
            }
            goto block_16;
        }
    }
}
