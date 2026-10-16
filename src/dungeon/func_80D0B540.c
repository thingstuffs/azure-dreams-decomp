/* Relink of matched dungeon/func_80CE7540; every changed retail word is a paired relocation. */
#define dungeonUpdateSteppedRgbFlash func_8014CD40
#include "modules/dungeon_ovl_7f469800_p01.h"

/* Fade the primitive color by one step and flag completion when the counter reaches zero. */
void func_8014CD40(void *fade_state, void *unused, T_80170D40_S_80170D40_1 *primitive)
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
        objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
    }
}
