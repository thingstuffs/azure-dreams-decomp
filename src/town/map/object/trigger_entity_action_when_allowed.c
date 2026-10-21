#include "common.h"
#include "shared/entity_objects.h"

#include "town/map/trigger_callbacks.h"

typedef map_trigger_record Entity;

extern s32 D_800C1F8C;
extern int abs(int);

extern s32 test_resident_bitmap_bit(s16);
extern void SD_Call(u16);

/* Triggers the entity action and updates its handler when its predicate and distance checks pass. */
void trigger_entity_action_when_allowed(Entity *entity)
{
    s32 x_distance;
    s32 y_distance;

    x_distance = abs(entity->x - view_reference_entity.x.w.i);
    y_distance = abs(entity->y - view_reference_entity.y.w.i);

    if (entity->mode == 0) {
        if (test_resident_bitmap_bit(entity->predicate_arg) == 0) {
            return;
        }
    } else {
        if (test_resident_bitmap_bit(entity->predicate_arg) != 0) {
            return;
        }
    }

    if ((s16)x_distance > entity->limit_x) {
        return;
    }
    if ((s16)y_distance > entity->limit_y) {
        return;
    }

    SD_Call(entity->argument);
    entity->handler = (map_trigger_callback_fn)&D_800C1F8C;
}
