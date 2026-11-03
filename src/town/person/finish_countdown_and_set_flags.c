#include "common.h"
#include "shared/object_flags.h"
#include "town/person.h"

#define FIELD_U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))


/* Decrement the countdown, setting completion flags on expiry or advancing the position. */
void finish_countdown_and_set_flags(TownObjectRecord *object, s32 *position) {
    u16 countdown;

    countdown = object->timer.as_u16 - 1;
    object->timer.as_u16 = countdown;
    if ((s16)countdown < 0) {
        FIELD_U16(object, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        *position += 0xFFEAAAAB;
    }
}
