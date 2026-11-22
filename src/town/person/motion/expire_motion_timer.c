#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/person/motion.h"

/* Decrements the timer and changes the handler and motion value when it becomes negative. */
void expire_motion_timer(TownObjectRecord *object, ObjectPosition *motion) {
    s16 remaining_ticks;

    remaining_ticks = object->timer - 1;
    object->timer = remaining_ticks;
    if (remaining_ticks < 0) {
        object->handler = &advance_motion_and_switch_handler;
        motion->velocity_z = 0xFFF60000;
    }
}
