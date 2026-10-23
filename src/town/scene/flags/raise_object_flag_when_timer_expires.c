#include "common.h"

typedef struct { s32 flags; } GlobalFlags;
extern GlobalFlags object_flag_block;
typedef struct { u16 unused; s16 timer; } Work;
/*
 * Decrements the work timer and sets local and global removal bit 0x8000 when the result is zero
 * or negative.
 */
void raise_object_flag_when_timer_expires(Work *work) {
    work->timer--;
    if (work->timer <= 0) {
        GlobalFlags *status = &object_flag_block;
        ((u16 *)work)[-1] |= 0x8000;
        status->flags |= 0x8000;
    }
}
