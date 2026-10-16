#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK, M2C_UNK);    /* extern */
s32 func_800BCB04(u16, u16, s16);                   /* extern */
M2C_UNK func_800C77D0(void *, void *, M2C_UNK, M2C_UNK); /* extern */
void *func_801688FC(void *, s32, s32, s16);         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80168AA4;
extern M2C_UNK D_8016A10C;
extern M2C_UNK D_8016A12C;

void func_80169494(void *arg0, void *arg1, void *arg2) {
    M2C_UNK var_a3;
    void *temp_a2;
    void *temp_s0;
    void *temp_s1;
    void *temp_t0;
    void *temp_t0_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, void **, 0x28) = arg0;
        M2C_FIELD(temp_s0, void **, 0x30) = NULL;
        M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80168AA4;
        func_8004491C(temp_v0, &D_80045340);
        temp_t0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_t0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_t0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_t0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, s8 *, 0x4C) = (s8) (M2C_FIELD(arg2, u8 *, 0x24) + *((((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 7) & 0x1C) + &D_8016A10C));
        M2C_FIELD(temp_s0, s8 *, 0x4D) = (s8) (M2C_FIELD(arg2, u8 *, 0x25) + M2C_FIELD(((((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 7) & 0x1C) + &D_8016A10C), u8 *, 2));
        M2C_FIELD(temp_t0, s16 *, 6) = 6;
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, s32 *, 0) = (s32) (((M2C_FIELD(temp_s0, s8 *, 0x4C) << 6) + 0x20) << 0x10);
        M2C_FIELD(temp_s1, s32 *, 4) = (s32) (((M2C_FIELD(temp_s0, s8 *, 0x4D) << 6) + 0x20) << 0x10);
        M2C_FIELD(temp_s1, s32 *, 8) = (s32) (func_800BCB04(M2C_FIELD(temp_s1, u16 *, 2), M2C_FIELD(temp_s1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x20)) << 0x10);
        M2C_FIELD(temp_s0, u16 *, 0x1A) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16) (((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 9) & 7);
        temp_t0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_t0_2, s16 *, 0x1C) = 0x2400;
        M2C_FIELD(temp_t0_2, s16 *, 0x1E) = 0x1C00;
        M2C_FIELD(temp_t0_2, s8 *, 0xE) = 0;
        M2C_FIELD(temp_t0_2, s8 *, 0xD) = 0;
        M2C_FIELD(temp_t0_2, s8 *, 0xC) = 0;
        M2C_FIELD(temp_v0, M2C_UNK *, 0x54) = M2C_UNALIGNED32(M2C_FIELD(&D_8016A12C, M2C_UNK *, 0));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x58) = M2C_UNALIGNED32(M2C_FIELD(&D_8016A12C, M2C_UNK *, 4));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x5C) = M2C_UNALIGNED32(M2C_FIELD(&D_8016A12C, M2C_UNK *, 8));
        M2C_FIELD(temp_t0_2, void **, 8) = (void *) (temp_v0 + 0x54);
        temp_v0_2 = func_801688FC(arg0, (s8) (u8) M2C_FIELD(temp_s0, s8 *, 0x4C) & 0xFFFF, (s8) (u8) M2C_FIELD(temp_s0, s8 *, 0x4D) & 0xFFFF, M2C_FIELD(temp_s1, s16 *, 0xA));
        M2C_FIELD(temp_s0, void **, 0x30) = temp_v0_2;
        if (temp_v0_2 != NULL) {
            temp_v1 = temp_v0_2 + 0x20;
            temp_a2 = M2C_FIELD(temp_v0_2, void **, 0xC);
            M2C_FIELD(temp_v1, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x14) | 0x100000);
            var_a3 = 0x3000;
            if (M2C_FIELD(temp_v1, s32 *, 0x1C) & 0x2000) {
                var_a3 = 0x300;
            }
            func_8009A3D0(M2C_FIELD(temp_a2, u8 *, 0x24), M2C_FIELD(temp_a2, u8 *, 0x25), var_a3, var_a3);
        }
        func_800C77D0(temp_v0, temp_s1, 8, 0x300);
    }
}
