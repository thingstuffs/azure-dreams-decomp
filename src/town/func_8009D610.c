#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"





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
void func_8009AD70(Rec_func_80094268_arg0 *state, Position *position, s32 context)
{
    u16 timer;
    s32 *target;

    target = D_800D0624;
    position->half_dx = (target[0] - position->x) / 2;
    position->half_dy = (target[1] - position->y) / 2;
    position->half_dz = (target[2] - position->z) / 2;

    timer = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = timer;
    if ((s16)timer < 0) {
        position->x = *(volatile s32 *)&D_800D0624[0];
        position->y = target[1];
        position->z = target[2];
        func_80099754(position);

        state->unk_30 = ((Rec_D_800E3D7C *)position)->unk_00.at02_u16.v;
        state->unk_32 = ((Rec_D_800E3D7C *)position)->unk_04.at02_u16.v;
        func_80094984(D_800D0078, state, context);

        state->unk_04.as_pv = D_8009AE88;
        state->unk_10.as_s16 = 0x400;
    }
}
