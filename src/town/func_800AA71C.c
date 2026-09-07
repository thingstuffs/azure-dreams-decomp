#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A7E7C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A7E7C_0_pre;   /* the 0x10 bytes before arg0 in func_800A7E7C, addressed as arg0[-1] */

typedef struct S_800A7E7C_0 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x32];
    u8 unk_96;
} S_800A7E7C_0;   /* arg0 in func_800A7E7C */

typedef struct S_800A7E7C_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_800A7E7C_1;   /* arg2 in func_800A7E7C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A7EC0;

void func_800A7E7C(void *arg0, M2C_UNK arg1, S_800A7E7C_1 *arg2) {
    ((S_800A7E7C_0_pre *)arg0)[-1].unk_00 = &D_800A7EC0;
    ((S_800A7E7C_0 *)arg0)->unk_60 = (s32) ((S_800A7E7C_0 *)arg0)->unk_96;
    arg2->unk_08 = &D_8006E240;
    func_80033CD8(arg0, &D_80045340);
}
