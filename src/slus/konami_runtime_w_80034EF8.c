#include "common.h"

#include "common.h"

extern u32 D_8008099C[];
extern u8 D_8007216C[];

extern void func_80037D50(u8 *arg0, u8 arg1);

void func_80034EF8(u8 *arg0, s32 arg1)
{
    u8 value;

    *(u32 *)0x8008099C = 0;
    func_80037D50(arg0, (u8)arg1);
    arg0[2] = arg1;
    arg0[0] = 0;
    arg0[1] = 0;
    value = D_8007216C[0];
    arg0[0x3D] = 0;
    *(u32 *)(arg0 + 0x34) = 0;
    arg0[0x3C] = value;
}
