#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();                   /* extern */
M2C_UNK func_8008F074();  /* extern */
M2C_UNK func_800C2CB0(); /* extern */
M2C_UNK func_800C337C();    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800D5028;

typedef struct S_800C3438_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
    u8 pad_80[0xC];
    s16 unk_8C;
    s16 unk_8E;
} S_800C3438_0;   /* arg0 in func_800C3438 */

void func_800C3438(S_800C3438_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80033CD8(arg0, &D_80045340);
    arg0->unk_8C = 0x40;
    arg0->unk_8E = 0x40;
    func_800C2CB0(arg0, arg2, **arg0->unk_7C, 0);
    func_8008F074(arg0, arg1, &D_800D5028);
    func_800C337C(arg0, arg1, arg2);
}
