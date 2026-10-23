#ifndef TOWN_PLAYER_OBJECT_INITIALIZATION_G00546_H
#define TOWN_PLAYER_OBJECT_INITIALIZATION_G00546_H
/* Initialize player object counters and fields (G00546). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D01E0. */

#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player/object/entity_record_fields.h"                     /* extern */
#include "m2c_compat.h"

typedef struct S_80098078_0 S_80098078_0;

extern s8 town_action_reset_byte;
void tick_countdown_and_initialize_target(S_80098078_0 *state, s32 value);
extern M2C_UNK target_action_update_address;

/* Functions defined in this translation unit. */
void initialize_object_with_count_four(Rec_func_80094268_arg0 *object, s32 setupValue, void *ptr2);
void initialize_object_with_value_800(Rec_func_80094268_arg0 *object, s32 setupContext, void *ptr2);

#endif
