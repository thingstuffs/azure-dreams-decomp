#include "modules/dungeon_ovl_1954800.h"
void draw_red(void *effect) {
    s32 ticks_left;
    s32 surface_height;
    s16 state;
    u16 final_display_y;
    S_81934C5C_3 *impact_sprite;
    S_81934C5C_2 *impact_effect;
    S_81934C5C_1 *owner;

    owner = ((S_81934C5C_0 *)effect)->unk_00;
    ((S_81934C5C_0 *)effect)->unk_48.s = (u16) (((S_81934C5C_0 *)effect)->unk_48.s - 1);
    owner->unk_0E = (u16) (owner->unk_0E | 0x8000);
    state = ((S_81934C5C_0 *)effect)->unk_4C;
    switch (state) {
    case 0:
        ((S_81934C5C_0 *)effect)->unk_48.s = 3U;
        ((S_81934C5C_0 *)effect)->unk_28.at02.v = -4;
        ((S_81934C5C_0 *)effect)->unk_30.at02.v = 0x10;
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);

                        /* fallthrough */
    case 1:
        ((S_81934C5C_0 *)effect)->unk_1C.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_1C.at00.v
            + ((S_81934C5C_0 *)effect)->unk_28.at00.v);
        ticks_left = ((S_81934C5C_0 *)effect)->unk_48.u;
        ((S_81934C5C_0 *)effect)->unk_24.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_24.at00.v
            + ((S_81934C5C_0 *)effect)->unk_30.at00.v);
        if (ticks_left > 0) {
            return;
        }
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);
        return;
    case 2:
        ((S_81934C5C_0 *)effect)->unk_1C.at00.v += ((S_81934C5C_0 *)effect)->unk_28.at00.v;
        ((S_81934C5C_0 *)effect)->unk_0C += (((S_81934C5C_0 *)effect)->unk_28.at02.v * 3) >> 2;
        ((S_81934C5C_0 *)effect)->unk_10 += (((S_81934C5C_0 *)effect)->unk_30.at02.v * 3) >> 2;
        ((S_81934C5C_0 *)effect)->unk_24.at00.v += ((S_81934C5C_0 *)effect)->unk_30.at00.v;
        surface_height = sample_terrain_surface_height(((S_81934C5C_0 *)effect)->unk_1C.at02.v,
            ((S_81934C5C_0 *)effect)->unk_20.at02.v, -0x400);
        if (surface_height >= 0x201) {
            if (((S_81934C5C_0 *)effect)->unk_24.at02.v > 0) {
                ((S_81934C5C_0 *)effect)->unk_4C = 0xFF;
                return;
            }
        }
        if (surface_height >= ((S_81934C5C_0 *)effect)->unk_24.at02.v) {
            return;
        }
        ((S_81934C5C_0 *)effect)->unk_24.at02.v = surface_height;
        impact_effect = func_8003FD64(0x312, ((M2C_UNK *)&D_80083498.next));
        if (impact_effect != NULL) {
            impact_effect->unk_10 = &D_80024928;
            impact_effect->unk_20 = (void *) ((S_81934C5C_0 *)effect)->unk_00;
            func_8004491C(impact_effect, func_80045340);
            impact_sprite = impact_effect->unk_0C;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_00 = (s32) ((S_81934C5C_0 *)effect)->unk_1C.at00.v;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_04 = (s32) ((S_81934C5C_0 *)effect)->unk_20.at00.v;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_08 = (s32) ((S_81934C5C_0 *)effect)->unk_24.at00.v;
            impact_sprite->unk_1E = 0x500;
            impact_sprite->unk_1C = 0x500;
            impact_sprite->unk_14 = (u16) (impact_sprite->unk_14 | 0xC);
            {
                s32 *animation;

                if (func_80069EF8() & 1) {
                    animation = &D_800DEDB0;
                } else {
                    animation = &D_800DEE38;
                }
                impact_sprite->unk_00 = animation;
                impact_sprite->unk_08 = (s32) ((S_81934C5C_4 *)animation)->unk_04;
                impact_sprite->unk_04 = 0;
                impact_sprite->unk_05 = 0;
            }
        }
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);
        return;
    case 3:
        ((S_81934C5C_0 *)effect)->unk_0C = (u16) (((S_81934C5C_0 *)effect)->unk_0C
            + ((s32) (((S_81934C5C_0 *)effect)->unk_28.at02.v * 3) >> 2));
        final_display_y = ((S_81934C5C_0 *)effect)->unk_10 + ((s32) (((S_81934C5C_0 *)effect)->unk_30.at02.v * 3) >> 2);
        ((S_81934C5C_0 *)effect)->unk_10 = final_display_y;
        if (((S_81934C5C_0 *)effect)->unk_24.at02.v < (s16) final_display_y) {
            ((S_81934C5C_0 *)effect)->unk_10 = (u16) ((S_81934C5C_0 *)effect)->unk_24.at02.v;
            ((S_81934C5C_0 *)effect)->unk_4C = 0xFF;
        }
        return;
    case 0xFF:
        ((S_81934C5C_0_pre *)effect)[-1].unk_00 = (u16) (((S_81934C5C_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
        return;
    default:
        return;
    }
}
