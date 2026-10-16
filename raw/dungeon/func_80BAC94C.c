#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_801620B4;
extern M2C_UNK D_80162108;
extern M2C_UNK D_80162FC0;

void func_8016214C(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v1;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 var_a1;
    s16 var_a1_2;
    s16 var_s3;
    s16 var_t0;
    s16 var_v0;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_v1_4;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a3;
    void *temp_a3_2;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x16);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) ((M2C_FIELD(arg0, u8 *, 4) * (0x32 - M2C_FIELD(arg0, s16 *, 0x1A))) / 10);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) ((M2C_FIELD(arg0, u8 *, 5) * (0x32 - M2C_FIELD(arg0, s16 *, 0x1A))) / 10);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) ((M2C_FIELD(arg0, u8 *, 6) * (0x32 - M2C_FIELD(arg0, s16 *, 0x1A))) / 10);
        if (M2C_FIELD(arg0, s16 *, 0x1A) < 0x29) {
            M2C_FIELD(arg0, s16 *, 0x16) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x16) + 1);
        }
        break;
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x1A) < 0xC) {
            M2C_FIELD(arg0, s16 *, 0x16) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x16) + 1);
        }
        break;
    case 2:
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) ((M2C_FIELD(arg0, u8 *, 4) * M2C_FIELD(arg0, s16 *, 0x1A)) / 10);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) ((M2C_FIELD(arg0, u8 *, 5) * M2C_FIELD(arg0, s16 *, 0x1A)) / 10);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) ((M2C_FIELD(arg0, u8 *, 6) * M2C_FIELD(arg0, s16 *, 0x1A)) / 10);
        break;
    }
    var_s3 = 0;
    M2C_FIELD(arg0, u16 *, 0x20) = (u16) (M2C_FIELD(arg0, u16 *, 0x20) + 1);
    do {
        temp_v0 = func_8003FC64(0x12);
        var_v0 = var_s3 + 1;
        if (temp_v0 != NULL) {
            temp_s1 = temp_v0 + 0x20;
            M2C_FIELD(temp_s1, s16 *, 0x1A) = 1;
            M2C_FIELD(temp_s1, s16 *, 0x1C) = 1;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80162108;
            func_8004491C(temp_v0, &D_801620B4);
            temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a3, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
            temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
            M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
            var_a1 = 0;
            M2C_FIELD(temp_v1_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
            temp_a3_2 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a3_2, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_a3_2, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_a3_2, s8 *, 0xE) = 0x80;
            M2C_FIELD(temp_a3_2, s8 *, 0xD) = 0x80;
            M2C_FIELD(temp_a3_2, s8 *, 0xC) = 0x80;
            do {
                temp_v1_3 = temp_s1 + ((s32) (var_a1 << 0x10) >> 0xE);
                M2C_FIELD(temp_v1_3, u8 *, 4) = (u8) M2C_FIELD(arg2, u8 *, 0xC);
                M2C_FIELD(temp_v1_3, u8 *, 5) = (u8) M2C_FIELD(arg2, u8 *, 0xD);
                temp_v0_2 = var_a1 + 1;
                var_a1 = temp_v0_2;
                M2C_FIELD(temp_v1_3, u8 *, 6) = (u8) M2C_FIELD(arg2, u8 *, 0xE);
            } while (temp_v0_2 < 4);
            if (var_s3 == 3) {
                M2C_FIELD(temp_s1, s8 *, 0xA) = 0;
                M2C_FIELD(temp_s1, s8 *, 9) = 0;
                M2C_FIELD(temp_s1, s8 *, 8) = 0;
                M2C_FIELD(temp_s1, s8 *, 6) = 0;
                M2C_FIELD(temp_s1, s8 *, 5) = 0;
                M2C_FIELD(temp_s1, s8 *, 4) = 0;
            }
            M2C_FIELD(temp_a3_2, s16 *, 6) = 0;
            M2C_FIELD(temp_s1, M2C_UNK *, 0x28) = M2C_UNALIGNED32(M2C_FIELD(&D_80162FC0, M2C_UNK *, 0));
            M2C_FIELD(temp_s1, M2C_UNK *, 0x2C) = M2C_UNALIGNED32(M2C_FIELD(&D_80162FC0, M2C_UNK *, 4));
            M2C_FIELD(temp_s1, M2C_UNK *, 0x30) = M2C_UNALIGNED32(M2C_FIELD(&D_80162FC0, M2C_UNK *, 8));
            var_t0 = 0;
            temp_a0 = temp_s1 + 0x28;
            M2C_FIELD(temp_a3_2, void **, 8) = temp_a0;
            M2C_FIELD(temp_a0, u8 *, 8) = (u8) (M2C_FIELD(temp_a0, u8 *, 8) + (M2C_FIELD(arg0, s16 *, 0x1E) * 4));
            temp_a0_2 = M2C_FIELD(temp_a3_2, void **, 8);
            M2C_FIELD(temp_a0_2, u8 *, 9) = (u8) (M2C_FIELD(temp_a0_2, u8 *, 9) + ((M2C_FIELD(arg0, u16 *, 0x20) & 3) * 8));
            do {
                var_a1_2 = 0;
                temp_v1_4 = var_t0 * 6;
loop_19:
                temp_a0_3 = var_a1_2 << 0x10;
                temp_v1_5 = var_a1_2 + 1;
                var_a1_2 = temp_v1_5;
                temp_a0_4 = temp_a0_3 >> 0xF;
                *(temp_a0_4 + (temp_v1_4 + temp_s1 + 0x64)) = *(temp_a0_4 + (temp_v1_4 + arg0 + 0x64));
                if (temp_v1_5 < 3) {
                    goto loop_19;
                }
                temp_v0_3 = var_t0 + 1;
                var_t0 = temp_v0_3;
            } while (temp_v0_3 < 4);
            temp_v0_4 = -((var_s3 + 1) * 0x10);
            temp_v1_6 = -(var_s3 * 0x10);
            M2C_FIELD(temp_s1, s16 *, 0x6E) = temp_v0_4;
            M2C_FIELD(temp_s1, s16 *, 0x68) = temp_v0_4;
            M2C_FIELD(temp_s1, s16 *, 0x7A) = temp_v1_6;
            M2C_FIELD(temp_s1, s16 *, 0x74) = temp_v1_6;
            var_v0 = var_s3 + 1;
        }
        var_s3 = var_v0;
    } while (var_v0 < 4);
    temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0x1A) - 1;
    M2C_FIELD(arg0, s16 *, 0x1A) = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
