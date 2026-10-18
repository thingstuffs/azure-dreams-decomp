#include "modules/dungeon_ovl_1930844.h"

void func_80024044(void *state, ovl_1930844_81910844_S_81910844_2 *motion, ovl_1930844_81910844_S_81910844_3 *visual) {
    s32 pos_x;
    s32 pos_y;
    s32 velocity_x;
    s32 velocity_y;
    s32 scale_step;
    u16 angle;
    u16 scale;
    s16 elapsed;
    s16 duration;
    ovl_1930844_81910844_S_81910844_1 *owner;

    owner = ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_00;
    owner->unk_14 =
        (u16) (owner->unk_14 + 1);
    ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_06.s =
        (u16) (((ovl_1930844_81910844_S_81910844_0 *)state)->unk_06.s + 1);
    pos_x = motion->unk_00;
    velocity_x = motion->unk_0C;
    pos_y = motion->unk_04;
    velocity_y = motion->unk_10;
    motion->unk_00 = pos_x + velocity_x;
    motion->unk_04 = pos_y + velocity_y;
    ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_0C =
        ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_0C + motion->unk_14;
    motion->unk_08 =
        ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_0C -
        ((func_800644B8((0x800 / (s16) ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_08) *
                        (s16) ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_06.s) >> 4) << 0xE);
    scale_step = 0x200 / (s16) ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_08;
    angle = visual->unk_1A;
    scale = visual->unk_1E;
    visual->unk_1A = angle + 0x300;
    scale = scale - scale_step;
    visual->unk_1E = scale;
    visual->unk_1C = scale;
    elapsed = ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_06.u;
    duration = ((ovl_1930844_81910844_S_81910844_0 *)state)->unk_08;
    if (elapsed > duration) {
        ((ovl_1930844_81910844_S_81910844_0_pre *)state)[-1].unk_00 =
            ((ovl_1930844_81910844_S_81910844_0_pre *)state)[-1].unk_00 | 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
