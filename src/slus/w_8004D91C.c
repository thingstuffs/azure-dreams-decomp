#include "common.h"

extern void func_8004D8F0(s32 arg0, u8 *arg1);

void func_8004D91C(s32 arg0, s16 *arg1)
{
    u8 sp10[4];

    func_8004D8F0(arg0 & 0xFF, sp10);
    arg1[0] = (s16)((sp10[0] >> 2) + 0x3C0);
    arg1[1] = (s16)(sp10[1] + 0x100);
    arg1[2] = (s16)(sp10[2] >> 2);
    arg1[3] = (s16)sp10[3];
}
