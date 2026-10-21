#ifndef TOWN_MAP_MIDPOINT_TRACKING_G00574_H
#define TOWN_MAP_MIDPOINT_TRACKING_G00574_H
/* Midpoint tracking shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A75EC, CL:town/func_800A76BC. */

#include "common.h"
#include "shared/vector.h"

typedef struct Func800A75ECState {
    s32 *current;
    s32 *previous;
    s32 center_x;
    s32 center_y;
    s32 center_z;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s32 unk24;
    void (*callback)(void *);
    s32 *other;
} Func800A75ECState;

typedef struct TownTransition {
    IntVector3 *target;
    IntVector3 *previous_target;
    s32 x;
    s32 y;
    s32 z;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 steps;
    s32 unk24;
    void (*callback)(void *, void *);
    IntVector3 *other;
} TownTransition;

/* Functions defined in this translation unit. */
void restart_or_update_midpoint_tracking(Func800A75ECState *state);
void reset_or_advance_target_midpoint(TownTransition *state);

#endif
