/* row func_8009AB4C, true base 0x800A02AC -- exemplar-seeded from landed
 * func_8009AC64 [true base 0x800A03C4] (MATCH @2.8.1-G0, gate_verified).
 * Opcode-sequence similarity 0.9655. Sole adaptation measured off the retail
 * stream: the check_entity_interaction_compatibility guard in the loop body is absent here (retail
 * drops the jal + its sll/beq test); register roles follow.
 * Ordinary code: no alias, no section attribute, no literal word arrays.
 */
#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/item.h"
#include "shared/object_node.h"

s32 check_diagonal_side_height(s32, u8, u8, s16);
void *find_eligible_actor_at_tile_and_height(void *, u16, u16, s16);

/* Check eight neighboring positions in cyclic order and return the first result that passes the direction check. */
void *find_adjacent_actor(ActorRecord *entity, u16 x, u16 y) {
    u16 *x_offsets;
    u16 *y_offsets;
    SpriteFrameState *entity_data;
    u16 base_x;
    u16 base_y;
    void *result;
    s32 attempt;
    s32 direction;

    base_x = x;
    base_y = y;
    x_offsets = dir_step_x;
    y_offsets = dir_step_y;
    entity_data = NODE_HEADER(entity)->sprite;
    direction = g_dungeon_status.turn_counter & 7;
    for (attempt = 0; attempt < 8; attempt++, direction = (direction + 1) & 7) {
        result = find_eligible_actor_at_tile_and_height(entity, (base_x + x_offsets[direction]) & 0xFFFF,
            (base_y + y_offsets[direction]) & 0xFFFF, entity->ground_height);
        if (result != 0) {
            if (((check_diagonal_side_height(direction, entity_data->tile_x, entity_data->tile_y,
                (s16)((u16)entity->ground_height - 0x20)) << 16) == 0)) {
                continue;
            }
            return result;
        }
    }
    return 0;
}
