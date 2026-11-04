#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/person.h"


/* Decrement the countdown, setting completion flags on expiry or advancing the position. */
void finish_countdown_and_set_flags(TownObjectRecord *object, s32 *position) {
    u16 countdown;

    countdown = object->timer.as_u16 - 1;
    object->timer.as_u16 = countdown;
    if ((s16)countdown < 0) {
        NODE_HEADER(object)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        *position += 0xFFEAAAAB;
    }
}
