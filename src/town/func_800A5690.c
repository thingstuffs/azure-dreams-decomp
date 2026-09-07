#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A2DF0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A2DF0_0;   /* arg0 in func_800A2DF0 */

typedef struct S_800A2DF0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A2DF0_1;   /* arg1 in func_800A2DF0 */

void func_800A2DF0(S_800A2DF0_0 *arg0, S_800A2DF0_1 *arg1) {
    arg0->unk_00 = (u16) (arg0->unk_00 + arg1->unk_02);
    arg0->unk_02 = (u16) (arg0->unk_02 + arg1->unk_06);
    arg0->unk_04 = (u16) (arg0->unk_04 + arg1->unk_0A);
}
