#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800CFCB4.h"

s32 func_800374F4();                         /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_8009F148(); /* extern */



typedef struct S_8009F374_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009F374_2;   /* arg3 in func_8009F374 */

void func_8009F374(Rec_D_800CFCB4 *arg0, M2C_UNK arg1, Rec_D_800E3D7C *arg2, S_8009F374_2 *arg3) {
    s16 temp_v0;
    s32 var_v0;
    s32 var_v0_2;

    arg2->unk_08.at00_s32.v = (s32) (arg0->unk_A0 + (((func_800374F4(0x10) & 0xFFFF) - 8) << 0x10));
    var_v0 = func_800644B8(arg0->unk_6C.as_s16 * 0x199);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    arg3->unk_1C = (s16) ((var_v0 >> 2) + 0x1000);
    var_v0_2 = func_800644B8(arg0->unk_6C.as_s16 * 0x199);
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    arg3->unk_1E = (s16) (0x1000 - (var_v0_2 >> 2));
    temp_v0 = (u16) arg0->unk_6C.as_s16 - 1;
    arg0->unk_6C.as_s16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg3->unk_1E = 0x1000;
        arg3->unk_1C = 0x1000;
        func_8009F148(arg0, arg1, arg2, arg3);
    }
}
