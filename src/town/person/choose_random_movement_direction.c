#include "common.h"
#include "town/person.h"
#include "shared/town_object.h"
#include "engine/window.h"


extern s32 D_800C355C;

/* Chooses a random movement direction and advances the entity state. */
void choose_random_movement_direction(TownObjectRecord *entity, ObjectPosition *movement, void *context) {
    s32 attempt;
    s32 direction;
    void *next_node;

    movement->velocity_x = 0;
    movement->velocity_y = 0;

    for (attempt = 0; attempt < 16; attempt++) {
        direction = scale_random_to_unsigned_halfword_limit(4) & 0xFFFF;

        if (direction == 0) {
            if (movement->x.w.i <
                entity->unk_84 + entity->unk_8C) {
                entity->heading = 0x400;
                break;
            }
        } else if (direction == 1) {
            if (movement->y.w.i <
                ((s16)entity->unk_86) + entity->unk_8E) {
                entity->heading = 0;
                break;
            }
        } else if (direction == 2) {
            if (entity->unk_84 - entity->unk_8C <
                movement->x.w.i) {
                entity->heading = 0xC00;
                break;
            }
        } else {
            if (((s16)entity->unk_86) - entity->unk_8E <
                movement->y.w.i) {
                entity->heading = 0x800;
                break;
            }
        }
    }

    next_node = *(void **)((u8 *)entity->unk_7C.as_pv + 4);
    initialize_object_entries(entity, context, next_node);
    entity->unk_50.as_pv = &D_800C355C;
}
