#include "common.h"
#include "town/person.h"
#include "shared/town_object.h"
#include "engine/window.h"


extern void D_800C355C(TownObjectRecord *, ObjectPosition *, SpriteFrameState *, s32);

/* Chooses a random movement direction and advances the entity state. */
void choose_random_movement_direction(TownObjectRecord *entity, ObjectPosition *movement, SpriteFrameState *context) {
    s32 attempt;
    s32 direction;
    void *next_node;

    movement->velocity_x = 0;
    movement->velocity_y = 0;

    for (attempt = 0; attempt < 16; attempt++) {
        direction = scale_random_by_limit(4) & 0xFFFF;

        if (direction == 0) {
            if (movement->x.w.i <
                entity->origin_x + entity->roam_range_x) {
                entity->heading = 0x400;
                break;
            }
        } else if (direction == 1) {
            if (movement->y.w.i <
                (entity->origin_y) + entity->roam_range_y) {
                entity->heading = 0;
                break;
            }
        } else if (direction == 2) {
            if (entity->origin_x - entity->roam_range_x <
                movement->x.w.i) {
                entity->heading = 0xC00;
                break;
            }
        } else {
            if ((entity->origin_y) - entity->roam_range_y <
                movement->y.w.i) {
                entity->heading = 0x800;
                break;
            }
        }
    }

    next_node = *(void **)((u8 *)entity->animation_tables.as_pv + 4);
    initialize_object_entries(entity, context, next_node);
    entity->state_callback.as_pv = D_800C355C;
}
