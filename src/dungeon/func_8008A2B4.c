#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009F644(); /* extern */
M2C_UNK func_800A56E0();                     /* extern */

typedef struct S_8008FA14_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008FA14_0;   /* arg0 in func_8008FA14 */

void func_8008FA14(S_8008FA14_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    arg0->unk_9A = 0x20;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    func_800A56E0(0x512);
    arg0->unk_A2 = (u16) (arg0->unk_A2 & 0xFFEF);
    func_8009F644(arg3, 0x30, arg0->unk_96, 0);
}
