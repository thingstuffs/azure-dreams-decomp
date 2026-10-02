#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003E240_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 pad[0x24];
} S_8003E240_0;   /* &D_800830C0 in func_8003E240 */

typedef struct S_8003E240_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 pad[0x24];
} S_8003E240_1;   /* &D_800830E8 in func_8003E240 */


extern S_8003E240_0 D_800830C0;
extern S_8003E240_1 D_800830E8;

/* Returns inverted input bits packed from the two valid input records. */
s32 func_8003E240(void) {
    s32 input_bits;

    input_bits = -1;
    if (D_800830C0.unk_00 == 0) {
        if ((u32) (D_800830C0.unk_01 - 0x20) < 0x51U) {
            input_bits = 0xFFFF0000;
            input_bits |= D_800830C0.unk_03 | (D_800830C0.unk_02 << 8);
        }
    }
    if ((D_800830E8.unk_00 == 0) && ((u32) (D_800830E8.unk_01 - 0x20)
        < 0x51U)) {
        input_bits = (input_bits & 0xFFFF) | ((D_800830E8.unk_03
            | (D_800830E8.unk_02 << 8)) << 0x10);
    }
    return ~input_bits;
}
