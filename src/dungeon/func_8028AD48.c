#include "dungeon/level/generate.h"

void retreat_generation_step_pair(void *step_state, s32 update_id)
{
    if (((s16 *) step_state)[2] > 0) {
        ((u16 *) step_state)[0] = (u16) (((u16 *) step_state)[0] - 1);
        ((u16 *) step_state)[1] = (u16) (((u16 *) step_state)[1] - 0x20);
        ((u16 *) step_state)[2] = (u16) (((u16 *) step_state)[2] - 1);
    }
}
