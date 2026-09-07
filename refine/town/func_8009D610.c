#include "common.h"

typedef struct S_8009AD70_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
} S_8009AD70_0;   /* arg0 in func_8009AD70 */

typedef struct S_8009AD70_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8009AD70_1;   /* arg1 in func_8009AD70 */



typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
    s32 half_dx;
    s32 half_dy;
    s32 half_dz;
} Position;

extern u8 D_8009AE88[];
extern u8 D_800D0078[];
extern s32 D_800D0624[];

extern void func_80094984();
extern void func_80099754();

/* Compute half the offset to the target, then snap to it and advance state when the timer expires. */
void func_8009AD70(S_8009AD70_0 *state, Position *position, s32 context)
{
    u16 timer;
    s32 *target;

    target = D_800D0624;
    position->half_dx = (target[0] - position->x) / 2;
    position->half_dy = (target[1] - position->y) / 2;
    position->half_dz = (target[2] - position->z) / 2;

    timer = state->unk_0A - 1;
    state->unk_0A = timer;
    if ((s16)timer < 0) {
        position->x = *(volatile s32 *)&D_800D0624[0];
        position->y = target[1];
        position->z = target[2];
        func_80099754(position);

        state->unk_30 = ((S_8009AD70_1 *)position)->unk_02;
        state->unk_32 = ((S_8009AD70_1 *)position)->unk_06;
        func_80094984(D_800D0078, state, context);

        state->unk_04 = D_8009AE88;
        state->unk_10 = 0x400;
    }
}
