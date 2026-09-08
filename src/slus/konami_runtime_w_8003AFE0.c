#include "common.h"

#include "common.h"

extern volatile s32 D_8006CD50[];
extern s32 D_80189394[3];
extern s32 D_801B8EB8[];

extern void func_801768AC(void);
extern void func_800411FC(u16 arg0);

/* Stores the selected table value and flags, then invokes the runtime handlers. */
void func_8003AFE0(s32 table_index, s32 flags)
{
    s32 table_value = D_8006CD50[table_index];

    D_80189394[0] = flags | 0x40000000;
    D_801B8EB8[0] = table_value;
    func_801768AC();
    func_800411FC(0);
}
