#include "common.h"

#include "common.h"

extern s32 D_8006CD50[];
extern s32 D_80189394[];
extern s32 D_801B8EB8[];
extern void func_801768AC(void);
extern void func_800411FC(u16);

/* Stores the supplied value and selected table entry, then invokes the runtime handlers. */
void func_8003AF94(s32 table_index, s32 value) {
    volatile s32 *table = D_8006CD50;
    s32 table_value = table[table_index];

    D_80189394[0] = value;
    D_801B8EB8[0] = table_value;
    func_801768AC();
    func_800411FC(0);
}
