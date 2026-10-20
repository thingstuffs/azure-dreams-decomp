#include "dungeon/monster/troll/troll_flash_effects.h"

/* Fade the primitive color by one step and flag completion when the counter reaches zero. */
void update_stepped_rgb_flash(void *fade_state, void *unused, T_80170D40_S_80170D40_1 *primitive)
{
    u16 steps_left;
    u8 red;

    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_02 = (u8)(((T_80170D40_S_80170D40_0 *)fade_state)->unk_02 - 0x40);
    red = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_00 - 0x40;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_00 = red;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_01 = (u8)(((T_80170D40_S_80170D40_0 *)fade_state)->unk_01 - 0x40);
    primitive->unk_0C = red;
    primitive->unk_0D = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_01;
    primitive->unk_0E = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_02;
    steps_left = ((T_80170D40_S_80170D40_0 *)fade_state)->unk_18 - 1;
    ((T_80170D40_S_80170D40_0 *)fade_state)->unk_18 = steps_left;
    if ((steps_left << 0x10) <= 0) {
        ((T_80170D40_S_80170D40_0_pre *)fade_state)[-1].unk_00 = (u16)(((T_80170D40_S_80170D40_0_pre *)fade_state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | 0x8000);
    }
}
