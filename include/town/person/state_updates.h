#ifndef TOWN_PERSON_STATE_UPDATES_H
#define TOWN_PERSON_STATE_UPDATES_H

#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"

void install_stored_value_handler(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *update_arg);
void initialize_object_assigns_state_data(TownObjectRecord *object, ObjectPosition *unusedArg, SpriteFrameState *initializationArg);
void wait_then_choose_direction(TownObjectRecord *entity, ObjectPosition *motion, SpriteFrameState *context, s32 update_arg);
void update_person_view_and_record(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *record);


void dispatch_status_triggered_update(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *status);
/* Registered code-address alias for dispatch_status_triggered_update. */
void person_table_handler_address(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *status);

void dispatch_object_state(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *dispatch_data);

void clear_record_indexed_flag(TownObjectRecord *state, ObjectPosition *unused_position, SpriteFrameState *unused_sprite);
void clear_record_indexed_byte(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

void initialize_actor_primary_handler(TownObjectRecord *actor, ObjectPosition *unused, SpriteFrameState *sprite);

void initialize_reaction_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

#endif
