#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 func_8009A8B0();
extern M2C_UNK D_8009A81C;

typedef struct S_8009A724_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x24];
    u16 unk_36;
    u16 unk_38;
} S_8009A724_0;   /* arg0 in func_8009A724 */

typedef struct S_8009A724_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8009A724_1;   /* arg1 in func_8009A724 */

void func_8009A724(S_8009A724_0 *arg0, S_8009A724_1 *arg1) {
    s16 temp_s0;
    s16 temp_s0_2;
    s16 temp_v1;

    temp_s0 = arg0->unk_36 - (func_800644B8(arg0->unk_10 - 0x80) / 48);
    temp_s0_2 = arg0->unk_38 - (func_80064584(arg0->unk_10 - 0x80) / 48);
    temp_v1 = arg0->unk_0A - 1;
    arg0->unk_0A = (u16) temp_v1;
    arg1->unk_02 = func_8009A8B0(temp_v1, arg1->unk_02, temp_s0);
    arg1->unk_06 = func_8009A8B0((s16) arg0->unk_0A, arg1->unk_06, temp_s0_2);
    if ((s16) arg0->unk_0A <= 0) {
        arg0->unk_0A = 0x10U;
        arg0->unk_04 = &D_8009A81C;
    }
}
