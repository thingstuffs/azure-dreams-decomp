#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/dir_step.h"

extern void *find_eligible_actor_at_tile_and_height(void *, s32, s32, s32);

/* Probe for an eligible actor at the directional neighbor and current height. */
void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction) {
    s32 direction_bits;
    u8 *x_offsets;
    s32 direction_offset;

    direction_bits = direction >> 8;
    x_offsets = ((u8 *)dir_step_x);
    direction_offset = direction_bits & 0xE;
    return find_eligible_actor_at_tile_and_height(
        entity,
        (*(u16 *)(x_offsets + direction_offset) + x) & 0xFFFF,
        (*(u16 *)(&((u8 *)dir_step_y)[direction_offset]) + y) & 0xFFFF,
        *(s16 *)((u8 *)entity + 0x88));
}
