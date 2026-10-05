#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


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
typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Vec3 D_800D0624;

extern void func_80094984();
extern void func_80099754();

/* Compute half the offset to the target, then snap to it and advance state when the timer expires. */
void func_8009AD70(Rec_func_80094268_arg0 *state, Position *position, s32 context)
{
    u16 timer;
    Vec3 *target;

    target = &D_800D0624;
    position->half_dx = (target->x - position->x) / 2;
    position->half_dy = (target->y - position->y) / 2;
    position->half_dz = (target->z - position->z) / 2;

    timer = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = timer;
    if ((s16)timer < 0) {
        position->x = target->x;
        position->y = target->y;
        position->z = target->z;
        func_80099754(position);

        state->unk_30 = ((u16)((EntityRec *)position)->x.w.i);
        state->unk_32 = ((u16)((EntityRec *)position)->y.w.i);
        func_80094984(D_800D0078, state, context);

        state->unk_04.as_pv = D_8009AE88;
        state->unk_10.as_s16 = 0x400;
    }
}
