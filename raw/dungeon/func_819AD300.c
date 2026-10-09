#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

extern u16 D_80027452[];

/* Update position, reduce movement speed, and flag completion when speed runs out. */
void func_80024B00(void *motion_data, s16 *position)
{
    s16 *motion = motion_data;
    s16 next_speed;
    u16 update_count = D_80027452[0];
    u16 z = position[5];
    u16 x = position[1];
    u16 y = position[3];

    D_80027452[0] = update_count + 1;
    if (position[5] < (s16)func_800BCB04(x, y, z + 2)) {
        ((s32 *)position)[0] -= (dirStepX[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[1] -= (dirStepY[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[2] += (0xC0 - motion[24]) << 10;
    }

    next_speed = (u16)motion[24] - 8;
    motion[24] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *)motion)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
