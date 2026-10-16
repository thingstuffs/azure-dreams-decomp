#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(void *, M2C_UNK *, M2C_UNK);  /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
s32 func_80069EF8(void *);                          /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80152D34;

void func_80153010(void *arg1, u16 arg3, s32 arg4, s32 arg5) {
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0xC) = 0x1E;
        M2C_FIELD(temp_s0, s16 *, 0xE) = 0x1E;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80152D34;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0_2;
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (temp_v0_2 | 2);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, u16 *, 2) = arg3;
        M2C_FIELD(temp_s1, u16 *, 6) = (u16) arg4;
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) arg5;
        M2C_FIELD(temp_s0, s32 *, 0x34) = 0x40000;
        M2C_FIELD(temp_s0, s32 *, 0x40) = 0x8000;
        M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32) ((s32) M2C_FIELD(temp_s1, s32 *, 0) >> 1);
        M2C_FIELD(temp_s0, s32 *, 0x30) = (s32) ((s32) M2C_FIELD(temp_s1, s32 *, 4) >> 1);
        if (M2C_FIELD(temp_s0, s32 *, 0x2C) == 0) {
            M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32) (((func_80069EF8(temp_a0) & 0x1F) - 0x10) << 0xF);
            M2C_FIELD(temp_s0, s32 *, 0x30) = (s32) (((func_80069EF8() & 0x1F) - 0x10) << 0xF);
        }
        M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) -((s32) M2C_FIELD(temp_s0, s32 *, 0x2C) >> 4);
        M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) -((s32) M2C_FIELD(temp_s0, s32 *, 0x30) >> 4);
        M2C_FIELD(temp_s1, u16 *, 2) = (u16) (M2C_FIELD(temp_s1, u16 *, 2) + M2C_FIELD(arg1, u16 *, 2));
        M2C_FIELD(temp_s1, u16 *, 6) = (u16) (M2C_FIELD(temp_s1, u16 *, 6) + M2C_FIELD(arg1, u16 *, 6));
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xA) + M2C_FIELD(arg1, u16 *, 0xA));
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0xC00;
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0xC00;
        M2C_FIELD(temp_a0_2, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_2, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_a0_2, &D_800DE870, 0);
    }
}
