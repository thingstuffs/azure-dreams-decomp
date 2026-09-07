#include "common.h"

#include "common.h"

extern volatile s32 D_8006CD50[];
extern s32 D_80189394[3];
extern s32 D_801B8EB8[];

extern void func_801768AC(void);
extern void func_800411FC(u16 arg0);

void func_8003AFE0(s32 arg0, s32 arg1)
{
    s32 value = D_8006CD50[arg0];

    D_80189394[0] = arg1 | 0x40000000;
    D_801B8EB8[0] = value;
    func_801768AC();
    func_800411FC(0);
}
