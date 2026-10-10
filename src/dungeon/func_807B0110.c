#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"


/* Updates position using decaying speed and sets completion flags when speed expires. */
void func_800F7910(void *motion_data, s16 *position) {
    s16 *motion = motion_data;
    s16 next_speed;

    if (position[5] < (s16)func_800BCB04((u16) position[1], (u16) position[3], position[5] + 2)) {
        ((s32 *) position)[0] -= (dirStepX[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[1] -= (dirStepY[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[2] += (0xC0 - motion[25]) << 10;
    }

    next_speed = (u16) motion[25] - 8;
    motion[25] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *) motion)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
