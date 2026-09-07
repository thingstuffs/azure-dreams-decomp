#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK func_80044A50();
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;

void func_800ACD74(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *temp_s0;
    u16 *state;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0x13;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    temp_s0 = arg0 - 0x20;
    state = (u16 *)&D_80083460;
    state[5] = (u16)(state[5] + 1);
    func_80044A50(temp_s0);
    func_8004491C(temp_s0, &D_800C6AEC);
    M2C_FIELD(arg2, s8 *, 0xF) = 0;
    M2C_FIELD(arg2, s8 *, 0xE) = 0;
    M2C_FIELD(arg2, s8 *, 0xD) = 0;
    M2C_FIELD(arg2, s8 *, 0xC) = 0;
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, u16 *, 0x12) = (u16)(M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
}
