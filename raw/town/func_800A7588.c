#include "common.h"

typedef struct Vec3i {
    u32 x;
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

extern Vec3i D_80100D98;
extern void func_800A4D4C(void *arg0, void *arg1);
extern void func_800A48F8(Vec3i *arg0);

void func_800A4CE8(TownTransition *state) {
    state->callback = func_800A4D4C;
    state->target = &D_80100D98;
    state->previous_target = &D_80100D98;
    state->other = &D_80100D98;
    state->x = D_80100D98.x;
    state->y = state->other->y;
    state->z = state->other->z;
    func_800A48F8((Vec3i *)&state->x);
}
