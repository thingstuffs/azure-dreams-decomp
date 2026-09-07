#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003E240_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8003E240_0;   /* &D_800830C0 in func_8003E240 */

typedef struct S_8003E240_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8003E240_1;   /* &D_800830E8 in func_8003E240 */


extern M2C_UNK D_800830C0;
extern M2C_UNK D_800830E8;

s32 func_8003E240(void) {
    s32 var_a0;

    var_a0 = -1;
    if (((S_8003E240_0 *)(&D_800830C0))->unk_00 == 0) {
        if ((u32) (((S_8003E240_0 *)(&D_800830C0))->unk_01 - 0x20) < 0x51U) {
            var_a0 = ((S_8003E240_0 *)(&D_800830C0))->unk_03 | (((S_8003E240_0 *)(&D_800830C0))->unk_02 << 8) | 0xFFFF0000;
        }
    }
    if ((((S_8003E240_1 *)(&D_800830E8))->unk_00 == 0) && ((u32) (((S_8003E240_1 *)(&D_800830E8))->unk_01 - 0x20) < 0x51U)) {
        var_a0 = (var_a0 & 0xFFFF) | ((((S_8003E240_1 *)(&D_800830E8))->unk_03 | (((S_8003E240_1 *)(&D_800830E8))->unk_02 << 8)) << 0x10);
    }
    return ~var_a0;
}
