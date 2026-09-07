#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A70EC_0 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x18];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
} S_800A70EC_0;   /* arg0 in func_800A70EC */

typedef struct S_800A70EC_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800A70EC_1;   /* arg3 in func_800A70EC */


s32 func_800644B8();                             /* extern */
M2C_UNK func_800A71D8();                            /* extern */

void func_800A70EC(S_800A70EC_0 *arg0, s32 arg1, s32 arg2, S_800A70EC_1 *arg3) {
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.s - 1;
    arg0->unk_6C.s = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg3->unk_1E = 0x1000;
        arg3->unk_1C = 0x1000;
        arg0->unk_50 = 0;
        return;
    }
    var_v0 = func_800644B8((s16) temp_v0 * 0xCC);
    if (var_v0 < 0) {
        var_v0 += 7;
    }
    arg3->unk_1C = (s16) ((var_v0 >> 3) + 0x1000);
    var_v0_2 = func_800644B8(arg0->unk_6C.u * 0xCC);
    if (var_v0_2 < 0) {
        var_v0_2 += 7;
    }
    arg3->unk_1E = (s16) ((var_v0_2 >> 3) + 0x1000);
    temp_v0_2 = func_800644B8(arg0->unk_6C.u * 0xCC);
    var_v1 = temp_v0_2 >> 3;
    if (temp_v0_2 < 0) {
        var_v1 = (s32) (temp_v0_2 + 7) >> 3;
    }
    arg3->unk_20 = (s16) (0x1000 - var_v1);
}
