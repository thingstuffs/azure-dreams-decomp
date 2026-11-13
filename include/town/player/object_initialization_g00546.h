#ifndef TOWN_PLAYER_OBJECT_INITIALIZATION_G00546_H
#define TOWN_PLAYER_OBJECT_INITIALIZATION_G00546_H
struct ObjectPosition;
/* Initialize player object counters and fields. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D01E0. */

#include "common.h"
#include "shared/position_views.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/object/entity_record_fields.h"                     /* extern */
#include "m2c_compat.h"


#include "town/player/action_reset_data.h"
void tick_countdown_and_initialize_target(UnsignedCountdownView *state, struct ObjectPosition *value);
/* Registered code-address alias for tick_countdown_and_initialize_target. */
void target_action_update_address(UnsignedCountdownView *state, s32 value);

/* Functions defined in this translation unit. */
void initialize_object_with_count_four(TownObjectRecord *object, struct ObjectPosition *setupValue, void *ptr2);
void begin_target_action_update(TownObjectRecord *object, struct ObjectPosition *setupContext, void *ptr2);

#endif
