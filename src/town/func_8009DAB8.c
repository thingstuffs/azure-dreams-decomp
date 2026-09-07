#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_8009BFD8();
M2C_UNK func_8009B29C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009B148;
extern M2C_UNK D_8009B2BC;


typedef struct S_8009B218_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_8009B218_0_pre;   /* the 0x10 bytes before arg0 in func_8009B218, addressed as arg0[-1] */

typedef struct S_8009B218_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x4];
    s32 unk_58;
    u8 pad_5C[0x30];
    s16 unk_8C;
    s16 unk_8E;
} S_8009B218_0;   /* arg0 in func_8009B218 */

typedef struct S_8009B218_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
} S_8009B218_1;   /* arg2 in func_8009B218 */

void func_8009B218(void *arg0, M2C_UNK arg1, S_8009B218_1 *arg2, s32 arg3) {
    ((S_8009B218_0_pre *)arg0)[-1].unk_00 = &D_8009B148;
    func_80033CD8(arg0, &D_80045340);
    ((S_8009B218_0 *)arg0)->unk_8C = 0;
    ((S_8009B218_0 *)arg0)->unk_8E = 0;
    arg2->unk_00 = 0;
    arg2->unk_04 = 0;
    arg2->unk_05 = 0;
    if (arg3 != 0) {
        ((S_8009B218_0 *)arg0)->unk_58 = arg3;
        func_8009BFD8(arg0, arg0, arg1, arg2);
        func_8009B29C();
        return;
    }
    ((S_8009B218_0 *)arg0)->unk_50 = &D_8009B2BC;
}
