#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/person.h"


/* Decrement the countdown, setting completion flags on expiry or advancing the position. */
void slide_until_countdown_expires(TownObjectRecord *object, s32 *position) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((s16)countdown < 0) {
        NODE_HEADER(object)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        *position += 0xFFEAAAAB;
    }
}
