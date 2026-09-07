#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_80033D08(void *);
extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C8B5C(void *, void *, s32);
extern void func_800C8D18(void);
extern void func_800C8D34(void *, void *, s32);
extern s32 D_800D636C[2];

void func_800C8C3C(void *arg0, void *arg1, s32 arg2)
{
    s32 *velocity;
    u16 temp_v0;

    velocity = D_800D636C;
    FIELD(arg1, s32, 0) += velocity[0];
    FIELD(arg1, s32, 4) += velocity[1];
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    if (func_800C2AE8(arg1) < FIELD(arg1, s16, 0xA)) {
        FIELD(arg1, s16, 0xA) = func_800C2AE8(arg1);
        temp_v0 = FIELD(arg0, u16, 0x90) - 1;
        FIELD(arg0, u16, 0x90) = temp_v0;
        if ((s16)temp_v0 < 0) {
            func_80033D08(arg0);
            func_800C8D34(arg0, arg1, arg2);
            func_800C8D18();
            return;
        }
        func_800C8B5C(arg0, arg1, arg2);
        func_800C8D18();
        return;
    }
    func_80095388(arg1);
}
