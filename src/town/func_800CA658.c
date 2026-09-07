#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C4174();
M2C_UNK func_800C7E58();

typedef struct S_800C7DB8_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x16];
    u16 unk_84;
    u16 unk_86;
} S_800C7DB8_0;   /* arg0 in func_800C7DB8 */

typedef struct S_800C7DB8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7DB8_1;   /* arg1 in func_800C7DB8 */

void func_800C7DB8(S_800C7DB8_0 *arg0, S_800C7DB8_1 *arg1) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((s16) temp_v0 <= 0) {
        func_800C4174(arg0);
        arg1->unk_02 = (u16) arg0->unk_84;
        arg1->unk_06 = (s16) arg0->unk_86;
        return;
    }
    arg1->unk_02 = (u16) (arg1->unk_02 + ((s32) ((s16) arg0->unk_84 - (s16) arg1->unk_02) / (s16) temp_v0));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) ((s16) arg0->unk_86 - arg1->unk_06) / (s16) arg0->unk_6C));
}
