#include "modules/dungeon_ovl_188898c.h"

void create_coordinate_sprite_object(void *owner, ovl_188898c_81868E84_S_81868E84_3 *coords) {
    u32 owner_value;
    u16 x;
    u16 y;
    u16 z;
    void *object;
    ovl_188898c_81868E84_S_81868E84_1 *state;
    ovl_188898c_81868E84_S_81868E84_4 *coord_pairs;

    object = func_8003FC64(0x212);
    if (object != 0) {
        ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_10 = (void *)animate_spiral_grayscale_effect;
        state = object + 0x20;
        ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        owner_value = ((ovl_188898c_81868E84_S_81868E84_2 *)owner)->unk_09;
        state->unk_06 = 0;
        state->unk_08 = 0;
        state->unk_0A = 0;
        state->unk_0C = owner;
        state->unk_10 = 0x40;
        state->unk_04 = owner_value;
        coord_pairs = ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_08;
        x = coords->unk_02;
        coord_pairs->unk_0E = x;
        coord_pairs->unk_02 = x;
        y = coords->unk_06;
        coord_pairs->unk_12 = y;
        coord_pairs->unk_06 = y;
        z = coords->unk_0A;
        coord_pairs->unk_16 = z;
        coord_pairs->unk_0A = z;
    }
}

/* MECHANISM: Hold owner[9] in a u32 local after the first two zero stores.
   Its live range claims $a0, leaving the allocator result in $a1; u32 avoids
   the redundant andi and collapses the +1-word branch-displacement cascade. */
