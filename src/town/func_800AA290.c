#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
/* extern */
typedef struct S_800A79F0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800A79F0_0;   /* arg0 in func_800A79F0 */

typedef struct S_800A79F0_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A79F0_1;   /* arg2 in func_800A79F0 */

/* extern */


M2C_UNK func_800A790C(S_800A79F0_0 *, s32, S_800A79F0_1 *, s32);
void func_800A79F0(S_800A79F0_0 *arg0, s32 arg1, S_800A79F0_1 *arg2, s32 arg3) {
    u16 temp_v0;
    s32 temp_v0_2;
    s32 var_v1;
    s32 var_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg2->unk_1E = 0x1000;
        arg2->unk_1C = 0x1000;
        func_800A790C(arg0, arg1, arg2, arg3);
        return;
    }
    temp_v0_2 = func_800644B8((s16) temp_v0 * 0xBA);
    var_v1 = temp_v0_2 >> 2;
    if (temp_v0_2 < 0) {
        var_v1 = (s32) (temp_v0_2 + 3) >> 2;
    }
    arg2->unk_1C = (s16) (0x1000 - var_v1);
    var_v0 = func_800644B8((s16) arg0->unk_6C * 0xBA);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    arg2->unk_1E = (s16) ((var_v0 >> 2) + 0x1000);
}
