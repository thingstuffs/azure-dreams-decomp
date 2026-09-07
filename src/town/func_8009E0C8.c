#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                 /* extern */
M2C_UNK func_8009C148(); /* extern */
extern s32 D_80083788;
extern s32 D_800D0428;

typedef struct S_8009B828_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009B828_0;   /* arg2 in func_8009B828 */

typedef struct S_8009B828_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009B828_1;   /* arg0 in func_8009B828 */

void func_8009B828(S_8009B828_1 *arg0, M2C_UNK arg1, S_8009B828_0 *arg2, M2C_UNK arg3) {
    s32 temp_a1;
    u16 temp_v0;

    temp_a1 = arg2->unk_08;
    arg2->unk_14 = (s32) ((s32) ((D_80083788 + D_800D0428) - temp_a1) / 2);
    func_8009539C(arg2, temp_a1);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_8009C148(arg0, arg1, arg2, arg3);
    }
}
