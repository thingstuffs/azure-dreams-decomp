#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/dir_step.h"
#include "dungeon/item.h"
struct Node;

extern void *find_eligible_actor_at_tile_and_height(struct Node *node, s32 x, s32 y_in, s16 value);

/* Probe for an eligible actor at the directional neighbor and current height. */
void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction) {
    s32 direction_bits;
    s32 direction_offset;

    direction_bits = direction >> 8;
    direction_offset = direction_bits & 0xE;
    return find_eligible_actor_at_tile_and_height(
        entity,
        ((u16)dir_step_x[direction_offset >> 1] + x) & 0xFFFF,
        ((u16)dir_step_y[direction_offset >> 1] + y) & 0xFFFF,
        *(s16 *)((u8 *)entity + 0x88));
}
