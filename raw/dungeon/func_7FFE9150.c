#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

void *func_7003CF18();
s32 func_700750E0();
M2C_UNK func_7010BD54();
extern s32 D_80086AD8;
extern u16 D_80094422;
extern M2C_UNK D_8010BA44;
extern Copy12 D_8010BF30;

void func_7FFE9150(void *arg0, void *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    u16 temp_v0_3;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v1;

    temp_a0 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg1, s16 *, 2) = (s16)(M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 2) + M2C_FIELD(arg0, u16 *, 0x3C));
    M2C_FIELD(arg1, s16 *, 6) = (s16)(M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 6) + M2C_FIELD(arg0, u16 *, 0x3E));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16)(M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0x40));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x16) + 1;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0;
    if ((s16)temp_v0 < 0x14) {
        temp_v0_2 = func_7003CF18(0x212);
        if (temp_v0_2 != 0) {
            func_7010BD54(temp_v0_2, arg0, arg1, arg2);
            temp_s0 = M2C_FIELD(temp_v0_2, void **, 8);
            M2C_FIELD(temp_v0_2, s16 *, 0x3E) = 0x14;
            M2C_FIELD(temp_v0_2, s16 *, 0x40) = 0x14;
            M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_8010BA44;
            M2C_FIELD(temp_s0, s32 *, 0) = (s32)((((func_700750E0() & 0x7FFF) - 0x4000) << 7) + M2C_FIELD(temp_s0, s32 *, 0));
            M2C_FIELD(temp_s0, s32 *, 4) = (s32)((((func_700750E0() & 0x7FFF) - 0x4000) << 7) + M2C_FIELD(temp_s0, s32 *, 4));
            temp_v1 = M2C_FIELD(temp_v0_2, void **, 0xC);
            M2C_FIELD(temp_v0_2, Copy12 *, 0x62) = D_8010BF30;
            M2C_FIELD(temp_v1, void **, 8) = (void *)((u8 *)temp_v0_2 + 0x62);
            M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x400;
        }
    }
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        u16 *global_count = &D_80094422;
        u16 next_global_count;

        M2C_FIELD(arg0, u16 *, -2) = (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        next_global_count = *global_count - 1;
        D_80086AD8 |= 0x8000;
        *global_count = next_global_count;
    }
}
