#ifndef TOWN_PERSON_ACTOR_OUTPUT_STATE_G00671_H
#define TOWN_PERSON_ACTOR_OUTPUT_STATE_G00671_H
/* G00671: shared declarations for actor output state. */
/* Original-file evidence (G00671): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CAA34. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800AB030_arg0.h"
#include "town/person/lookup_motion.h"

/* extern */
typedef struct S_800C81E4_0 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800C81E4_0;

/* arg0 in update_output_adding_eight_state */
typedef struct S_800C81E4_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800C81E4_1;

/* extern */
s32 query_lowered_transform_position();

/* Functions defined in this translation unit. */
void update_output_adding_eight_state(Rec_func_800AB030_arg0 *state, S_800C81E4_1 *output);

#endif
