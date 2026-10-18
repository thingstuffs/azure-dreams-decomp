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
extern void restart_or_update_midpoint_tracking(void *first_ptr, void *second_ptr);
extern void apply_and_store_setting(Vec3i *setting);

// Initializes the town transition callback, targets, and position from D_80100D98.
void initialize_transition_state(TownTransition *state) {
    state->callback = restart_or_update_midpoint_tracking;
    state->target = &D_80100D98;
    state->previous_target = &D_80100D98;
    state->other = &D_80100D98;
    state->x = D_80100D98.x;
    state->y = state->other->y;
    state->z = state->other->z;
    apply_and_store_setting((Vec3i *)&state->x);
}
