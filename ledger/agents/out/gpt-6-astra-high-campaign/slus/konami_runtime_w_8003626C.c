#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003626C_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 pad_4D[0x3];
    s8 unk_50;
    u8 pad_51[0x17];
    M2C_UNK * unk_68;
} S_8003626C_0;   /* arg0 in func_8003626C */


extern s32 D_80083170;
extern M2C_UNK func_800362A0;

/* Resets state fields and selects the next handler when either trigger bit is set. */
void func_8003626C(S_8003626C_0 *state) {
    if (D_80083170 & 0x60) {
        state->unk_4C = 0xFF;
        state->unk_50 = 0;
        state->unk_68 = &func_800362A0;
    }
}
