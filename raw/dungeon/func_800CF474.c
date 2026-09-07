#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 D_80045340;
extern s32 D_800DECF8;

void func_800D4BD4(void *arg0, void *arg1, void *arg2)
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v1;
    void *state;
    s32 copied_value;
    u16 flags;

    state = (u8 *)arg0 + 0x20;
    FIELD(state, void *, 0x24) = arg1;
    func_8004491C(arg0, &D_80045340);
    temp_a0 = FIELD(arg0, void *, 0xC);
    FIELD(temp_a0, s16, 0x10) = 0x20;
    FIELD(temp_a0, u16, 0x14) = FIELD(temp_a0, u16, 0x14) | 0xC;
    temp_v1 = FIELD(arg0, void *, 8);
    FIELD(temp_v1, u16, 2) = FIELD(arg2, u16, 2);
    FIELD(temp_v1, u16, 6) = FIELD(arg2, u16, 6);
    FIELD(temp_v1, u16, 0xA) = FIELD(arg2, u16, 0xA);
    temp_a0_2 = FIELD(arg0, void *, 0xC);
    FIELD(temp_a0_2, s16, 0x1E) = 0x800;
    FIELD(temp_a0_2, s16, 0x1C) = 0x800;
    FIELD(state, s32, 0xC) = FIELD(arg1, s32, 0xC);
    copied_value = FIELD(arg1, s32, 0xC);
    flags = FIELD(temp_a0_2, u16, 0x14);
    FIELD(temp_a0_2, s16, 0x12) = 0x7DCF;
    flags |= 0x100;
    FIELD(temp_a0_2, s32, 0xC) = copied_value;
    FIELD(temp_a0_2, u16, 0x14) = flags;
    func_8003DB94(temp_a0_2, &D_800DECF8, 0);
}
