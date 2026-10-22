#include "common.h"
#include "shared/object_flags.h"

#define FIELD_U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))


/* Decrement the countdown, setting completion flags on expiry or advancing the position. */
void finish_countdown_and_set_flags(void *object, s32 *position) {
    u16 countdown;

    countdown = FIELD_U16(object, 0x6C) - 1;
    FIELD_U16(object, 0x6C) = countdown;
    if ((s16)countdown < 0) {
        FIELD_U16(object, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        *position += 0xFFEAAAAB;
    }
}
