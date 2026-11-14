#include "common.h"
#include "shared/town_object.h"

#include "town/person/object_setup.h"
#include "town/person/state_updates.h"
#include "town/person.h"

/* Count down after an unhandled entity update and choose a direction when the timer expires. */
void wait_then_choose_direction(TownObjectRecord *entity, void *motion, SpriteFrameState *context, s32 update_arg) {
    u16 ticks_left;

    if (select_object_setup_path(entity, motion, context) == 0) {
        ticks_left = entity->timer - 1;
        entity->timer = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            choose_random_movement_direction(entity, motion, context);
        }
    }
}
