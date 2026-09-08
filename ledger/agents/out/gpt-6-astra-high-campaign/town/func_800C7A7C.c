#include "common.h"
#include "m2c_compat.h"

extern u8 D_80082660;
extern M2C_UNK D_800C5100;

typedef struct S_800C51DC_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C51DC_0;   /* arg0 in func_800C51DC */

typedef struct S_800C51DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800C51DC_1;   /* arg1 in func_800C51DC */

/* Clear the actor table flag, install its handler, and initialize state values. */
void func_800C51DC(S_800C51DC_0 *actor, S_800C51DC_1 *state) {
    *((actor->unk_60 * 8) + &D_80082660) = 0;
    actor->unk_54 = &D_800C5100;
    state->unk_10 = 0x80000;
    state->unk_14 = 0x40000;
}
