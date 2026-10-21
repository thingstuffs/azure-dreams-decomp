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

extern Vec3i town_position_reference_state;
extern void restart_or_update_midpoint_tracking(void *first_ptr, void *second_ptr);
extern void apply_and_store_setting(Vec3i *setting);

// Initializes the town transition callback, targets, and position from D_80100D98.
void initialize_transition_state(TownTransition *state) {
    state->callback = restart_or_update_midpoint_tracking;
    state->target = &town_position_reference_state;
    state->previous_target = &town_position_reference_state;
    state->other = &town_position_reference_state;
    state->x = town_position_reference_state.x;
    state->y = state->other->y;
    state->z = state->other->z;
    apply_and_store_setting((Vec3i *)&state->x);
}
