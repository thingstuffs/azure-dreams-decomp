#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800374F4();
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A8440;
extern M2C_UNK D_800D1464;

void *func_800A84D0(void *arg0) {
    s32 temp_s0_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800A8440;
        func_8004491C(temp_v0, &D_80045340);
        M2C_FIELD(temp_s1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
        M2C_FIELD(temp_s1, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 6);
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        func_8003DB94(temp_s0, &D_800D1464, 0);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0xFF;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 2) = (s16) (temp_s0_2 + func_800374F4(7));
    }
    return temp_v0;
}

/* MECHANISM: Preserve the seed's 0x28 frame and s3/s2/s1/s0 held-value layout.
   Unsigned byte stores force li 0x00ff at word 33; signed s8 had emitted li -1. */
