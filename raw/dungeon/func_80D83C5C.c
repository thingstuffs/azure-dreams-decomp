#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(void *, M2C_UNK *, M2C_UNK);  /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, void *);   /* extern */
s32 func_80069EF8(void *);                          /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_800E2468;
extern M2C_UNK D_80153384;

void func_8015345C(void *arg0, u16 arg1) {
    u16 temp_v0_3;
    u16 temp_v1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a1;
    void *temp_a2;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80153384;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 2) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) - 0x58);
        temp_s0 = ((arg1 >> 7) & 0x1C) + &D_800E2468;
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, u16 *, 2) = (u16) (M2C_FIELD(temp_a0, u16 *, 2) + (M2C_FIELD(temp_s0, s16 *, 0) * 0x12));
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 6) + (M2C_FIELD(temp_s0, s16 *, 2) * 0x12));
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s16 *, 6) = 6;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32) (((func_80069EF8(temp_a0_2) & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) * 0x10);
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a1, s32 *, 0xC) + (M2C_FIELD(temp_s0, s16 *, 0) * 0x1C0000));
        temp_a2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a2, s32 *, 0x10) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x10) + (M2C_FIELD(temp_s0, s16 *, 2) * 0x1C0000));
        temp_v0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, u16 *, 0xA) = arg1;
        M2C_FIELD(temp_v0_2, s16 *, 0xC) = 0xC;
        M2C_FIELD(temp_v0_2, s16 *, 0xE) = 0xC;
        func_8004491C(temp_v0, &D_80045340, temp_a2);
        temp_a0_3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_3, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_a0_3, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a0_3, s16 *, 0x1E) = 0x800;
        temp_v0_3 = M2C_FIELD(temp_a0_3, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_a0_3, u16 *, 0x14) = temp_v0_3;
        temp_v1 = temp_v0_3 | 2;
        M2C_FIELD(temp_a0_3, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_3, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_3, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_3, u16 *, 0x14) = temp_v1;
        M2C_FIELD(temp_a0_3, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_a0_3, u16 *, 0x14) = (u16) (temp_v1 | 0x100);
        func_8003DB94(temp_a0_3, &D_800DE870, 0);
    }
}
