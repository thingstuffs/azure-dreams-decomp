#ifndef TOWN_PERSON_TIMED_ACTOR_MOTION_G00677_H
#define TOWN_PERSON_TIMED_ACTOR_MOTION_G00677_H
/* G00677: shared declarations for timed actor motion. */
/* Original-file evidence (G00677): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6268. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/object/initialize_object_entries_api.h"          /* extern */

typedef struct S_800C8FF0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C8FF0_1;

extern M2C_UNK D_800C8FF0;
extern M2C_UNK D_800D6268;
void finish_countdown_and_set_flags(void *object, s32 *position);

/* Functions defined in this translation unit. */
void advance_object_after_timeout_variant_2(Rec_func_80094268_arg0 *object, s32 unused, s32 updateContext);
void decrement_entity_timer_updating_motion(Rec_func_80094268_arg0 *entity, S_800C8FF0_1 *motion, s32 context);

#endif
