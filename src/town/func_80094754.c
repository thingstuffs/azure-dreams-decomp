#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80091F48();
extern M2C_UNK func_80093D48();
extern M2C_UNK func_80095C80();

typedef struct S_80091EB4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x28];
    s16 unk_34;
} S_80091EB4_0;   /* arg0 in func_80091EB4 */

typedef struct S_80091EB4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80091EB4_1;   /* arg1 in func_80091EB4 */

void func_80091EB4(S_80091EB4_0 *arg0, S_80091EB4_1 *arg1, M2C_UNK arg2) {
    s32 temp_v1;
    u16 temp_v0;

    func_80095C80(arg1);
    temp_v0 = arg0->unk_0A - 1;
    temp_v1 = arg0->unk_34 << 0x10;
    arg0->unk_0A = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg1->unk_0C = 0;
        arg1->unk_10 = 0;
        arg1->unk_14 = 0;
        arg1->unk_08 = (s32) (arg0->unk_34 << 0x10);
        func_80093D48(arg0, arg1, arg2);
        return;
    }
    arg1->unk_14 =
        (s32) ((s32) (temp_v1 - arg1->unk_08) /
               (s16) temp_v0);
}
