#include "dungeon/monster/noise/move_fade_and_accelerate_effect.h"

/* Move and fade the effect, apply vertical acceleration, and flag it when its lifetime ends. */
void move_fade_and_accelerate_effect(T_80170F0C_S_func_80D1170C_1 *effect, IntVector3 *position)
{
    s16 life_left;
    s32 red;
    s32 green;
    s32 blue;
    s32 color_product;
    s32 *flag_page;

    position->x += effect->unk_40;
    position->y += effect->unk_44;
    position->z += effect->unk_48;

    color_product = effect->unk_00 * effect->unk_32.unk_32;
    red = color_product / effect->unk_34;
    effect->unk_04.bytes.unk_04 = red;
    color_product = effect->unk_01 * effect->unk_32.unk_32;
    green = color_product / effect->unk_34;
    effect->unk_04.bytes.unk_05 = green;
    color_product = effect->unk_02 * effect->unk_32.unk_32;
    blue = color_product / effect->unk_34;

    effect->unk_48 += effect->unk_54;
    life_left = effect->unk_32.unk_32_u;
    life_left -= 1;
    effect->unk_32.unk_32_u = life_left;
    effect->unk_04.bytes.unk_06 = blue;
    effect->unk_08 = effect->unk_04.unk_04;

    if ((life_left << 16) <= 0) {
        ((ObjectRetirementFlags *)((u8 *)effect - 2))->unk_00 |= 0x8000;
        flag_page = (s32 *)0x80080000;
        flag_page[0x14A0 / sizeof(s32)] =
            flag_page[0x14A0 / sizeof(s32)] | 0x8000;
    }
}

/* MECHANISM: Storing red and green immediately after their divisions invalidates
   the shared scale/divisor loads before scheduling; the stores then schedule late. */
