#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008CBA0_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x3A];
    union { u8 u8; u16 u16; } unk_64;   /* accessed as both */
} S_8008CBA0_0;   /* arg3 in func_8008CBA0 */


void func_8008CBA0(s32 arg0, s32 arg1, s32 arg2, S_8008CBA0_0 *arg3) {
    u8 temp_v0;
    u8 temp_v1;

    temp_v0 = arg3->unk_28 + arg3->unk_64.u8;
    temp_v1 = arg3->unk_29;
    arg3->unk_28 = temp_v0;
    if (temp_v1 < (u32) (temp_v0 & 0xFF)) {
        arg3->unk_28 = temp_v1;
    }
    arg3->unk_64.u16 = 0;
}
