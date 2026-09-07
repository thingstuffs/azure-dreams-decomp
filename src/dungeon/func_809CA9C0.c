#include "common.h"
#include "m2c_compat.h"

typedef struct S_801721C0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801721C0_0;   /* arg0 in func_801721C0 */


M2C_UNK func_800A4ACC();                     /* extern */
s32 func_800AB1C0();                                /* extern */
M2C_UNK func_800AD594();            /* extern */
s32 func_800AD9B4();                /* extern */
extern u16 D_80083462;
extern M2C_UNK D_80170E54;

void func_801721C0(S_801721C0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    if (func_800AB1C0() != 0) {
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            arg0->unk_8C = &D_80170E54;
            goto block_3;
        }
    } else {
block_3:
        if (D_80083462 & 0x80) {
            arg0->unk_90.at02.v = 0;
            arg0->unk_90.at00.v = 0;
        }
    }
}
