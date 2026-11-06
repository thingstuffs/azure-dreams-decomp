#ifndef DUNGEON_ACTOR_PHASE_BODY_H
#define DUNGEON_ACTOR_PHASE_BODY_H

#include "common.h"

/* Payload allocated by create_default_state_object and updated by advance_object_phase_counters. */
typedef struct ObjectPhaseBody {
    u16 ticks;
    s16 state;
    s16 unk_04;
    u16 offset;
    u16 phase;
} ObjectPhaseBody;

void advance_object_phase_counters(ObjectPhaseBody *body);

#endif
