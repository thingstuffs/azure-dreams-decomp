#include "dungeon/item/monster_koyaw_g00324.h"
#include "dungeon/item.h"

/* Blends three source channels toward 0x80 using a triangular phase weight. */
void compute_pulsing_tint_offsets(u8 *src, s8 *dst)
{
    s16 weight;
    s32 delta_0;
    s32 delta_1;
    s32 delta_2;
    weight = g_game_work.frame_counter;
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
            koyaw_data = mp_empty_status_tint_color;
        } else if (flags & 0x20) {
            koyaw_data = paralyzed_status_tint_color;
        } else if (flags & 0x40) {
            koyaw_data = poisoned_status_tint_color;
        } else if (flags & 0x400) {
            koyaw_data = confused_status_tint_color;
        } else if (flags & 0x10) {
            koyaw_data = blind_status_tint_color;
        } else {
            {

                koyaw_data = neutral_status_tint_color;
            }
        }
        if (koyaw_data != 0) {
            compute_pulsing_tint_offsets(koyaw_data, dst);
        }
    }
}
