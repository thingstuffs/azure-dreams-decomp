#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 func_8009A8B0();
extern M2C_UNK D_8009A81C;

typedef struct S_8009A724_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x24];
    u16 unk_36;
    u16 unk_38;
} S_8009A724_0;   /* arg0 in func_8009A724 */

typedef struct S_8009A724_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8009A724_1;   /* arg1 in func_8009A724 */

/* Move toward an angle-offset target and advance state when the timer expires. */
void func_8009A724(S_8009A724_0 *state, S_8009A724_1 *position) {
    s16 target_x;
    s16 target_z;
    s16 frames_left;

    target_x = state->unk_36 - (func_800644B8(state->unk_10 - 0x80) / 48);
    target_z = state->unk_38 - (func_80064584(state->unk_10 - 0x80) / 48);
    frames_left = state->unk_0A - 1;
    state->unk_0A = (u16) frames_left;
    position->unk_02 = func_8009A8B0(frames_left, position->unk_02, target_x);
    position->unk_06 = func_8009A8B0((s16) state->unk_0A, position->unk_06, target_z);
    if ((s16) state->unk_0A <= 0) {
        state->unk_0A = 0x10U;
        state->unk_04 = &D_8009A81C;
    }
}
