#ifndef INCLUDE_TOWN_SYSTEM_OBJECT_HOOKS_H
#define INCLUDE_TOWN_SYSTEM_OBJECT_HOOKS_H

#include "common.h"

void noop_user_data_object(void);


struct Rec_func_80094268_arg0;
void decrement_object_timer_and_update(struct Rec_func_80094268_arg0 *object, s32 callback_arg_1, s32 callback_arg_2);
/* Registered code-address alias for decrement_object_timer_and_update. */
void person_countdown_update_address(struct Rec_func_80094268_arg0 *object, s32 callback_arg_1, s32 callback_arg_2);

#endif
