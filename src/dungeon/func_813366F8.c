#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A4ACC();                      /* extern */

typedef struct S_8016D6F8_0 {
    u8 pad_00[0x6D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8016D6F8_0;   /* arg3 in func_8016D6F8 */

typedef struct S_8016D6F8_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8016D6F8_1;   /* arg0 in func_8016D6F8 */

void func_8016D6F8(S_8016D6F8_1 *arg0, M2C_UNK arg1, M2C_UNK arg2, S_8016D6F8_0 *arg3) {
    arg3->unk_71 = (u8) (arg3->unk_71 & 0x7F);
    arg0->unk_8C = 0;
    arg0->unk_9A = 0x17;
    arg0->unk_9B = 0;
    func_800A4ACC(arg3);
    arg3->unk_6D = (u8) (arg3->unk_6D - 1);
}
