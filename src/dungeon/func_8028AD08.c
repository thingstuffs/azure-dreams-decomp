#include "dungeon/level/generate.h"

void advance_generation_step_pair(void *step_state, s32 update_id)
{
    if ((*((u16 *) (((u8 *) step_state) + 4))) < 9) {
        *((u16 *) (((u8 *) step_state) + 0)) = (*((u16 *) (((u8 *) step_state) + 0))) + 1;
        *((u16 *) (((u8 *) step_state) + 2)) = (*((u16 *) (((u8 *) step_state) + 2))) + 0x20;
        *((u16 *) (((u8 *) step_state) + 4)) = (*((u16 *) (((u8 *) step_state) + 4))) + 1;
    }
}
