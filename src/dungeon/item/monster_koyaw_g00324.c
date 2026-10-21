/* Monster koyaw (G00324). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_8009A9F0. */
#include "dungeon/item/monster_koyaw_g00324.h"

/* Blends three source channels toward 0x80 using a triangular phase weight. */
void itm_mon_koyaw_set(u8 *src, s8 *dst)
{
    s16 weight;
    s32 delta_0;
    s32 delta_1;
    s32 delta_2;
    weight = g_game_work.unk_004;
    weight &= 0x1F;
    if (weight & 0x10) {
        weight = (-weight) & 0x1F;
        if (weight == 0) {
            weight = 0x10;
        }
    }
    delta_0 = (0x80 - src[0]) * weight;
    if (delta_0 < 0) {
        delta_0 += 15;
    }
    delta_0 = ((u32) delta_0) >> 4;
    delta_1 = (0x80 - src[1]) * weight;
    if (delta_1 < 0) {
        delta_1 += 15;
    }
    delta_1 = ((u32) delta_1) >> 4;
    delta_2 = (0x80 - src[2]) * weight;
    if (delta_2 < 0) {
        delta_2 += 15;
    }
    delta_2 = ((u32) delta_2) >> 4;
    dst[0] = (-0x80) - delta_0;
    dst[1] = (-0x80) - delta_1;
    weight = delta_2;
    dst[2] = (-0x80) - weight;
}

/* Selects koyaw data from the flags and applies it unless disabled. */
void apply_monster_koyaw_data(s32 flags, s8 *dst) {
    if (!(flags & 0x10000000)) {
        void *koyaw_data;
        if (flags & 8) {
            koyaw_data = (void *)D_800DD844;
        } else if (flags & 0x20) {
            koyaw_data = (void *)D_800DD850;
        } else if (flags & 0x40) {
            koyaw_data = (void *)D_800DD848;
        } else if (flags & 0x400) {
            koyaw_data = (void *)D_800DD840;
        } else if (flags & 0x10) {
            koyaw_data = (void *)D_800DD84C;
        } else {
            {

                koyaw_data = (void *)D_800DD83C;
            }
        }
        if (koyaw_data != 0) {
            itm_mon_koyaw_set(koyaw_data, dst);
        }
    }
}
