#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048E00();

typedef struct S_800B6580_0 {
    u8 pad_00[0x3C];
    u8 unk_3C;
} S_800B6580_0;   /* arg0 in func_800B6580 */

void func_800B6580(S_800B6580_0 *arg0, s16 arg1) {
    s16 sp[4];

    sp[0] = 0xC6;
    sp[1] = 6;
    sp[3] = arg1;
    sp[2] = 0x76;
    func_80048E00(arg0, &sp[0]);
    arg0->unk_3C = (u8)(arg0->unk_3C | 0x80);
}
