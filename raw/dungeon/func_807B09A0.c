#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEED0;
extern M2C_UNK D_800F89B8;

void func_807B09A0(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_3;
    u16 temp_v0;
    void *temp_s0;
    void *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, u16 *, 8) + 1;
    M2C_FIELD(arg0, u16 *, 8) = temp_v0;
    if (temp_v0 & 1) {
        temp_v0_2 = func_8003FD64(0x312, &D_80083498);
        if (temp_v0_2 != NULL) {
            M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800F89B8;
            func_8004491C(temp_v0_2, &D_80045340);
            temp_s0 = M2C_FIELD(temp_v0_2, void **, 0xC);
            temp_a0 = (M2C_FIELD(arg0, u16 *, 0) + (rand() % 48)) - 0x18;
            M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s16 *, 2) = temp_a0;
            temp_a0_2 = (M2C_FIELD(arg0, u16 *, 2) + (rand() % 48)) - 0x18;
            M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s16 *, 6) = temp_a0_2;
            M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s16 *, 0xA) = (u16) (M2C_FIELD(arg0, u16 *, 4) - (rand() & 7));
            M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0xC) = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0x10) = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            M2C_FIELD(temp_s0, s16 *, 0x1E) = 0xC00;
            M2C_FIELD(temp_s0, s16 *, 0x1C) = 0xC00;
            M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_s0, M2C_UNK **, 0) = &D_800DEED0;
            M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
            temp_v0_3 = M2C_FIELD(&D_800DEED0, s32 *, 4);
            M2C_FIELD(temp_s0, s8 *, 4) = 0;
            M2C_FIELD(temp_s0, s8 *, 5) = 0;
            M2C_FIELD(temp_s0, s32 *, 0xC) = 0xA0A0A0;
            M2C_FIELD(temp_s0, s32 *, 8) = temp_v0_3;
        }
    }
}
