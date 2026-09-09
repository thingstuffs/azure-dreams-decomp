#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C7E70_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u16 unk_6E;
    u8 pad_70[0x2];
    u16 unk_72;
} S_800C7E70_0;   /* arg0 in func_800C7E70 */


M2C_UNK func_800C4174(S_800C7E70_0 *, M2C_UNK, M2C_UNK);
void func_800C7E70(S_800C7E70_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_72 = (u16) arg0->unk_6E;
        func_800C4174(arg0, arg1, arg2);
    }
}
