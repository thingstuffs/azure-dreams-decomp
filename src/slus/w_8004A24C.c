#include "common.h"
#include "m2c_compat.h"

/* first_pass warm draft: compiles, best score 46 @ 2.7.2 */
#include "common.h"

typedef struct S_8004A24C_0 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_8004A24C_0;   /* arg0 in func_8004A24C */


M2C_UNK func_80049F68();                            /* extern */
M2C_UNK func_8004A030();       /* extern */
s32 func_8004A0C0();                         /* extern */
s32 func_8004A10C();                             /* extern */
M2C_UNK func_8004A170();       /* extern */
s32 func_8004DC14();                /* extern */

void func_8004A24C(S_8004A24C_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, s16 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    u16 var_s1;
    s32 arg5_s0;

    func_80049F68(arg0);
    arg0->unk_1C = func_8004A0C0(arg1);
    temp_v0 = func_8004DC14(arg2, 1);
    arg5_s0 = arg5;
    var_s1 = arg5_s0;
    arg0->unk_18 = temp_v0;
    arg5_s0 = (s16)arg5_s0;
    if (arg5_s0 == -1) {
        var_s1 = func_8004A10C(temp_v0) + 0x20;
    }
    func_8004A170(arg0, arg0->unk_08, var_s1 & 0xFFFF, arg0->unk_00 & 1);
    arg0->unk_14 = (s32) arg0->unk_08;
    func_8004A030(arg0, arg3, (s16) arg4, (s16) var_s1);
}
