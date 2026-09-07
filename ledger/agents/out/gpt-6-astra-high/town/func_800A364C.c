#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800A1080();
extern M2C_UNK func_800A12B4();
extern M2C_UNK D_800A0E3C[3];
extern M2C_UNK D_80100B70[3];

typedef struct S_800A0DAC_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u16 unk_6E;
} S_800A0DAC_0;   /* arg0 in func_800A0DAC */

/* Advance the state counter and apply the next state when the check succeeds. */
void func_800A0DAC(S_800A0DAC_0 *state, M2C_UNK unused, M2C_UNK context_a, M2C_UNK context_b) {
    func_800A12B4(&D_80100B70, context_a, context_b);
    state->unk_6E = (u16)(state->unk_6E + 0x10);
    if (func_800A1080(&D_80100B70, context_a, context_b) != 0) {
        state->unk_6C = 0x20;
        state->unk_50 = &D_800A0E3C;
    }
}
