#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_801720D0;
extern void *D_80174CD8;

void func_80172160(void)
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v1;
    s32 random;
    s32 coord;

    temp_s2 = M2C_FIELD(D_80174CD8, void **, 8);
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x16) = 0x1E;
        M2C_FIELD(temp_v1, s16 *, 0x18) = 0x1E;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801720D0;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s32 *, 0) = M2C_FIELD(temp_s2, s32 *, 0);
        M2C_FIELD(temp_s0, s32 *, 4) = M2C_FIELD(temp_s2, s32 *, 4);
        M2C_FIELD(temp_s0, s32 *, 8) = M2C_FIELD(temp_s2, s32 *, 8);
        random = rand(temp_a0);
        coord = M2C_FIELD(temp_s0, u16 *, 2);
        random &= 0x3F;
        coord -= 0x20;
        coord += random;
        M2C_FIELD(temp_s0, u16 *, 2) = coord;
        random = rand();
        coord = M2C_FIELD(temp_s0, u16 *, 6);
        random &= 0x3F;
        coord -= 0x20;
        coord += random;
        M2C_FIELD(temp_s0, u16 *, 6) = coord;
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) |= 0x80;
        func_8003DB94(temp_a0_2, &D_800DE870, 0);
    }
}

/* MECHANISM: The 32-byte frame holds the source, allocated object, and copied object
   across calls in s2, s1, and s0. Split random-coordinate RMWs keep -0x20 as
   per-use addiu operations instead of a shared saved-register constant. */
