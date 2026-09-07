#include "common.h"

typedef struct S_80123238_0_pre {
    s8 unk_00;
    u8 pad_01[0x6];
    s8 unk_07;
    s8 unk_08;
    s8 unk_09;
} S_80123238_0_pre;   /* the 0xA bytes before var_a1 in func_80123238, addressed as var_a1[-1] */

typedef struct S_80123238_0 {
    s8 unk_00;
} S_80123238_0;   /* var_a1 in func_80123238 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Row {
    u8 f0;
    s8 f1;
    s8 f2;
    s8 f3;
    s16 f4;
    s16 f6;
    s8 f8;
    s8 f9;
    s8 f10;
    s8 f11;
} Row;

extern Row D_801331D0[0x10];

void func_80123238(void)
{
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a2;
    s8 *var_a1;
    Row *var_a3;

    var_a3 = &D_801331D0[0];
    var_a2 = 0;
    do {
        var_a1 = (s8 *)var_a3 + 0xB;
        var_a3->f0 = 0xC0;
        ((S_80123238_0_pre *)var_a1)[-1].unk_00 = 0x2C;
        (*(s8 *)((u8 *)var_a1 + -9)) = 0;
        (*(s8 *)((u8 *)var_a1 + -8)) = 0;
        (*(s16 *)((u8 *)var_a1 + -7)) = 6;
        (*(s16 *)((u8 *)var_a1 + -5)) = 0x7C81;
        temp_a0 = var_a2 / 3;
        temp_v1 = var_a2 % 3;
        var_a2 += 1;
        ((S_80123238_0_pre *)var_a1)[-1].unk_07 = (s8)(temp_v1 * 0x48);
        ((S_80123238_0_pre *)var_a1)[-1].unk_08 = (s8)((temp_a0 * 0x10) - 0x80);
        ((S_80123238_0_pre *)var_a1)[-1].unk_09 = 0x48;
        ((S_80123238_0 *)var_a1)->unk_00 = 0x10;
        var_a3 += 1;
    } while (var_a2 < 0x10);
}
