#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033D08();
M2C_UNK func_8008F134();
s32 func_80096FF4();
M2C_UNK func_800970AC();
M2C_UNK func_8009B1FC();
s32 func_8009CFE0();
extern s32 D_800814A0[];


typedef struct S_8009B148_0_pre {
    u16 unk_00;
} S_8009B148_0_pre;   /* the 0x2 bytes before arg0 in func_8009B148, addressed as arg0[-1] */

typedef struct S_8009B148_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(void *, void *, M2C_UNK, M2C_UNK);
    u8 pad_54[0x44];
    s8 * unk_98;
} S_8009B148_0;   /* arg0 in func_8009B148 */

void func_8009B148(void *arg0, M2C_UNK arg1, M2C_UNK arg2)
{
    M2C_UNK held_arg1 = arg1;
    register M2C_UNK held_arg2 ASM_REG("$18") = arg2;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s8 *temp_v0;

    if (func_8009CFE0() != 0) {
        func_8008F134(arg0);
        temp_v0 = ((S_8009B148_0 *)arg0)->unk_98;
        if (temp_v0 != 0) {
            *temp_v0 = 0;
        }
        func_80033D08(arg0);
        ((S_8009B148_0_pre *)arg0)[-1].unk_00 =
            (u16)(((S_8009B148_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_8009B1FC();
        return;
    }
    ((S_8009B148_0 *)arg0)->unk_50(
        arg0, arg0, held_arg1, held_arg2);
    if (!(((S_8009B148_0_pre *)arg0)[-1].unk_00 & 0x8000)) {
        func_800970AC(func_80096FF4(held_arg1), arg0);
    }
}
