/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "m2c_compat.h"

typedef s8 M2C_UNK8;

M2C_UNK func_800C2CB0();
s32 func_800C2D0C();

typedef struct S_800C2D34_0 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x4];
    s32 * unk_78;
} S_800C2D34_0;   /* arg0 in func_800C2D34 */

typedef struct S_800C2D34_1 {
    u8 pad_00[0x5];
    s8 unk_05;
} S_800C2D34_1;   /* arg1 in func_800C2D34 */

void func_800C2D34(S_800C2D34_0 *arg0, S_800C2D34_1 *arg1, s32 *arg2) {
    arg0->unk_78 = arg2;
    func_800C2CB0(arg0, arg1, arg0->unk_78[func_800C2D0C(arg0->unk_72)], 0);
    arg1->unk_05 = 0;
}
