#include "common.h"

#define M2C_FIELD(p, type, off) (*(type)((u8 *)(p) + (off)))

typedef s32 M2C_UNK;

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;
extern M2C_UNK D_80173FF4;

void func_8017406C(void *arg0, void *arg1) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_s3 = arg1;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x1A) = 0xF;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80173FF4;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s32 *, 0x40) = (s32)M2C_FIELD(temp_s3, s32 *, 0);
        M2C_FIELD(temp_s0, s32 *, 0x44) = (s32)M2C_FIELD(temp_s3, s32 *, 4);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16)M2C_FIELD(temp_s3, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16)M2C_FIELD(temp_s3, u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16)M2C_FIELD(temp_s3, u16 *, 0xA);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_s1, u8 *, 0xE) = 0x60U;
        M2C_FIELD(temp_s1, u8 *, 0xD) = 0xFFU;
        M2C_FIELD(temp_s1, u8 *, 0xC) = 0xFFU;
        M2C_FIELD(temp_v0, u8 *, 0x20) = 0xFFU;
        M2C_FIELD(temp_s0, u8 *, 1) = (u8)M2C_FIELD(temp_s1, u8 *, 0xD);
        M2C_FIELD(temp_s0, u8 *, 2) = (u8)M2C_FIELD(temp_s1, u8 *, 0xE);
        func_8003DB94(temp_s1, &D_800DEC70, rand() & 1);
        M2C_FIELD(temp_s1, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s1, u16 *, 0x14) | 0x100);
    }
}
