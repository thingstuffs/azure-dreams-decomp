#ifndef INCLUDE_TOWN_SYSTEM_OBJECT_HOOKS_H
#define INCLUDE_TOWN_SYSTEM_OBJECT_HOOKS_H

#include "common.h"

void noop_user_data_object(void);


struct TownObjectRecord;
struct ObjectPosition;
struct SpriteFrameState;
void run_setup_on_timer_expiry(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);
/* Registered code-address alias for run_setup_on_timer_expiry. */
void person_countdown_update_address(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

#endif
