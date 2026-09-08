#include "common.h"

extern void func_800478B8(void *);
extern s32 func_800644B8(s16);
extern s32 func_80064584(s16);
extern s32 D_800814A0[];

/* Updates radial position or sets completion flags based on the object state. */
void func_80174F64(u16 *motion, s32 *position, u8 *object)
{
    s32 y_offset;

    motion[0]++;
    func_800478B8(object);
    if (*(u16 *)(object + 0x14) & 0x6000) {
        motion[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    motion[3] += motion[4];
    position[0] = position[3] + (((func_80064584((s16)motion[2]) >> 4) *
                           (s16)motion[3]) << 8);
    y_offset = (func_800644B8((s16)motion[2]) >> 4) * (s16)motion[3];
    *(u16 *)((u8 *)position + 0xA) -= 2;
    position[1] = position[4] + (y_offset << 8);
}
