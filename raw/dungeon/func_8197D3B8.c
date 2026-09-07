#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800478B8(void *);
extern s32 D_800814A0[3];

void func_8197D3B8(void *arg0, void *arg1, void *arg2)
{
    s32 delta_y;
    s32 delta_z;
    void *primitive;

    delta_y = FIELD(arg1, s32, 0x10);
    delta_z = FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0x0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 0x4) += delta_y;
    FIELD(arg1, s32, 0x8) += delta_z;

    primitive = FIELD(arg0, void *, 0x0);
    FIELD(primitive, u16, 0x52) |= 0x8000;

    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
