#include "common.h"

extern u8 D_800D3814[12];
extern u16 D_80082E76;

extern void func_80041094(s32 a0, s16 a1, s16 a2, s16 a3, s32 a4);

/* Stores the state and passes centered grid coordinates to func_80041094. */
void func_800B9204(s8 state)
{
    D_800D3814[6] = state;
    func_80041094(0xC, ((D_800D3814[0] + 1) << 6) | 0x20,
                   ((D_800D3814[1] + 1) << 6) | 0x20, -0x100,
                   D_80082E76);
}
