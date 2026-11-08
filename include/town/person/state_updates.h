#ifndef TOWN_PERSON_STATE_UPDATES_H
#define TOWN_PERSON_STATE_UPDATES_H

#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"

void install_stored_value_handler(void *object, void *unused, void *update_arg);
void initialize_object_assigns_state_data(TownObjectRecord *object, void *unusedArg, void *initializationArg);
void run_unhandled_update_and_choose_direction(TownObjectRecord *entity, void *motion, SpriteFrameState *context, s32 update_arg);
void update_person_view_and_record(void *ptr, void *value, SpriteFrameState *record);


void dispatch_status_triggered_update(TownObjectRecord *handler_arg, void *context, SpriteFlagsView *status);
/* Registered code-address alias for dispatch_status_triggered_update. */
void person_table_handler_address(void *handler_arg, void *context, SpriteFlagsView *status);

void dispatch_object_state(TownObjectRecord *object, void *context, void *dispatch_data);

void clear_record_indexed_flag(TownObjectRecord *state, s32 unused_context, void *unused_state_context);
void clear_record_indexed_byte(void *state, s32 unused_context, void *unused_state_context);

void initialize_actor_primary_handler(TownObjectRecord *actor, ObjectPosition *unused, void *output);

void initialize_reaction_object(TownObjectRecord *object, void *unused, void *context);

#endif
