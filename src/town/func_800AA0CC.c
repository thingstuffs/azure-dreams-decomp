#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A782C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in func_800A782C, addressed as arg0[-1] */

typedef struct S_800A782C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800A782C_1;   /* arg1 in func_800A782C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800A790C();
M2C_UNK func_800C2CB0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A78AC;
extern M2C_UNK D_800F842C;

void func_800A782C(void *arg0, S_800A782C_1 *arg1, M2C_UNK arg2) {
    ((S_800A782C_0_pre *)arg0)[-1].unk_00 = &D_800A78AC;
    func_800C2CB0(arg0, arg2, &D_800F842C, 0);
    func_80033CD8(arg0, &D_80045340);
    arg1->unk_0A = 0;
    func_800A790C(arg0, arg1, arg2);
}
