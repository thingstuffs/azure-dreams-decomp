#ifndef TOWN_PERSON_ACTOR_OUTPUT_STATE_G00671_H
#define TOWN_PERSON_ACTOR_OUTPUT_STATE_G00671_H
/* shared declarations for actor output state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CAA34. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800AB030_arg0.h"
#include "town/person/lookup_motion.h"

/* arg0 in raise_object_while_counter_runs */

/* extern */
s32 query_lowered_transform_position();

/* Functions defined in this translation unit. */
void raise_object_while_counter_runs(Rec_func_800AB030_arg0 *state, ObjectPosition *output);

#endif
