#include "common.h"

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct TownTransition {
    Vec3i *target;
    Vec3i *previous_target;
    s32 x;
    s32 y;
    s32 z;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 steps;
    s32 unk24;
    void (*callback)(void *, void *);
    Vec3i *other;
} TownTransition;

extern void func_800A4D4C(void *arg0, void *arg1);
extern void func_800A4F3C(void);

void func_800A4E1C(TownTransition *state) {
    Vec3i *target;

    target = state->target;
    if (target != state->previous_target) {
        Vec3i *saved_target = target;

        ASM_KEEP(saved_target);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        state->steps = 9;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->previous_target = saved_target;
        func_800A4D4C(state, state);
        return;
    }

    state->x += (((target->x + state->other->x) / 2) - state->x) /
                state->steps;
    state->y +=
        (((state->target->y + state->other->y) / 2) - state->y) /
        state->steps;
    state->z +=
        (((state->target->z + state->other->z) / 2) - state->z) /
        state->steps;
    state->steps--;
    if (state->steps <= 0) {
        state->callback = func_800A4D4C;
    }
}
