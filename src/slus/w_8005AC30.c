#include "common.h"

extern s16 poll_driver_completion_event(s32 a0);

/* Checks SPU transfer completion, waiting when requested. */
s16 sound_check_or_wait_for_spu_transfer(s16 wait_for_completion)
{
    if (!wait_for_completion)
        return poll_driver_completion_event(0);
    return poll_driver_completion_event(1);
}
