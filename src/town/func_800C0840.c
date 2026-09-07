#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BDFA0_0 {
    u8 pad_00[0x68];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x36];
    s32 unk_A0;
    s32 unk_A4;
} S_800BDFA0_0;   /* arg0 in func_800BDFA0 */


s32 func_800352FC();                                /* extern */
M2C_UNK func_8003DB94();       /* extern */
M2C_UNK func_800478B8();                     /* extern */
M2C_UNK func_800BE07C();                /* extern */
M2C_UNK func_800BE0BC();                            /* extern */
s32 func_800C2AB4();                          /* extern */

void func_800BDFA0(S_800BDFA0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v1;

    func_800478B8(arg2);
    temp_v1 = arg0->unk_68.s;
    switch (temp_v1) {
    case 0:
        if ((func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
            func_8003DB94(arg2, arg0->unk_A4, 0);
            arg0->unk_68.u++;
        }
        break;
    case 1:
        if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
            arg0->unk_68.u++;
        }
        break;
    case 2:
        if ((func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
            func_8003DB94(arg2, arg0->unk_A0, 0);
            arg0->unk_68.u++;
        }
        break;
    case 3:
        if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
            arg0->unk_68.s = 0;
        }
        break;
    }
}
