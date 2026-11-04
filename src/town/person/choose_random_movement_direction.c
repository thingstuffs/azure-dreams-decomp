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
                entity->unk_84.as_s16 + entity->unk_8C.as_s16) {
                entity->heading.as_s16 = 0x400;
                break;
            }
        } else if (direction == 1) {
            if (movement->y.w.i <
                entity->unk_86.as_s16 + entity->unk_8E.as_s16) {
                entity->heading.as_s16 = 0;
                break;
            }
        } else if (direction == 2) {
            if (entity->unk_84.as_s16 - entity->unk_8C.as_s16 <
                movement->x.w.i) {
                entity->heading.as_s16 = 0xC00;
                break;
            }
        } else {
            if (entity->unk_86.as_s16 - entity->unk_8E.as_s16 <
                movement->y.w.i) {
                entity->heading.as_s16 = 0x800;
                break;
            }
        }
    }

    next_node = *(void **)((u8 *)entity->unk_7C.as_pv + 4);
    initialize_object_entries(entity, context, next_node);
    entity->unk_50.as_pv = &D_800C355C;
}
