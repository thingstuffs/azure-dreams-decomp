#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern struct {
    s8 pad[0xA];
    u16 field_0xA;
} D_80083460;

typedef struct S_800ACB98_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_800ACB98_0;   /* arg0 in func_800ACB98 */

typedef struct S_800ACB98_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800ACB98_1;   /* arg2 in func_800ACB98 */

typedef struct S_800ACB98_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800ACB98_2;   /* arg3 in func_800ACB98 */

void func_800ACB98(S_800ACB98_0 *arg0, void *arg1, S_800ACB98_1 *arg2, S_800ACB98_2 *arg3) {
    arg0->unk_9A = 0x14;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg2->unk_14 = (u16)(arg2->unk_14 | 0x800);
    arg0->unk_96 = 0;
    D_80083460.field_0xA = D_80083460.field_0xA + 1;
    arg3->unk_1C = (s32)(arg3->unk_1C | 0x10000000);
}
