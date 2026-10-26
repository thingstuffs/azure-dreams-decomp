#ifndef TOWN_PERSON_STATE_UPDATES_H
#define TOWN_PERSON_STATE_UPDATES_H

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/sprite_frame_state.h"

void install_stored_value_handler(void *object, void *unused, void *update_arg);
void initialize_object_assigns_state_data(Rec_func_80094268_arg0 *object, void *unusedArg, void *initializationArg);
void run_unhandled_update_and_choose_direction(Rec_func_80094268_arg0 *entity, void *motion, void *context, s32 update_arg);
void update_person_view_and_record(void *ptr, void *value, SpriteFrameState *record);


void dispatch_status_triggered_update(void *handler_arg, void *context, SpriteFlagsView *status);
/* Registered code-address alias for dispatch_status_triggered_update. */
void person_table_handler_address(void *handler_arg, void *context, SpriteFlagsView *status);

#endif
