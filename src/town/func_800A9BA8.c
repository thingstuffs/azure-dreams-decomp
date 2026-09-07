#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A7360;
extern s32 D_800D0DF8[];

typedef struct S_800A7308_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A7308_0;   /* arg1 in func_800A7308 */

typedef struct S_800A7308_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A7308_1;   /* arg0 in func_800A7308 */

void func_800A7308(S_800A7308_1 *arg0, S_800A7308_0 *arg1) {
    arg1->unk_14 = D_800D0DF8[arg0->unk_90];
    arg0->unk_50 = &D_800A7360;
}
