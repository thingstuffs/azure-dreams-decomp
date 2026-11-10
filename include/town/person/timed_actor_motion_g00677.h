#ifndef TOWN_PERSON_TIMED_ACTOR_MOTION_G00677_H
#define TOWN_PERSON_TIMED_ACTOR_MOTION_G00677_H
/* shared declarations for timed actor motion. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6268. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object/initialize_object_entries_api.h"          /* extern */
#include "shared/entity.h"

extern void D_800C8FF0();
extern s32 D_800D6268[];
void finish_countdown_and_set_flags(TownObjectRecord *object, s32 *position);

/* Functions defined in this translation unit. */
void advance_object_after_timeout_variant_2(TownObjectRecord *object, s32 unused, void *updateContext);
void decrement_entity_timer_updating_motion(TownObjectRecord *entity, ObjectPosition *motion, void *context);

#endif
