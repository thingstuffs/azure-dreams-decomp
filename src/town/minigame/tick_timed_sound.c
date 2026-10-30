#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "slus.h"
#include "town/minigame.h"

   /* the 0x2 bytes before arg0 in tick_timed_sound, addressed as arg0[-1] */





/* Starts a timed state and sets completion flags when its countdown expires. */
void tick_timed_sound(TimedSoundObject *object)
{
    s16 state;
    u16 timer;

    state = object->state.s;
    if (state != 0) {
        if (state != 1) {
            return;
        }
    } else {
        SD_Call(0x603);
        object->state.u = object->state.u + 1;
    }

    timer = object->timer - 1;
    object->timer = timer;
    if ((timer << 16) <= 0) {
        SD_Call(0x1603);
        ((ObjectStatusPrefix16 *)object)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
