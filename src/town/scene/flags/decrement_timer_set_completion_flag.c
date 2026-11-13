#include "common.h"
#include "town/minigame/object.h"
#include "town/scene/flags.h"
#include "shared/object_flags.h"

/*
 * Decrements the work timer and sets local and global removal bit 0x8000 when the result is zero
 * or negative.
 */
void decrement_timer_and_set_completion_flag(SpawnDisplayObject *work) {
    work->timer--;
    if (work->timer <= 0) {
        ObjectFlagBlock *status = &object_flag_block;
        ((u16 *)work)[-1] |= 0x8000;
        status->flags |= 0x8000;
    }
}
