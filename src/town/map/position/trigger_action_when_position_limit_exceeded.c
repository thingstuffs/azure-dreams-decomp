#include "common.h"
#include "shared/entity_objects.h"

#include "town/map/trigger_callbacks.h"

typedef map_trigger_record S_800C1F8C_0;   /* arg0 in trigger_action_when_position_limit_exceeded */


typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void SD_Call(s32);
extern s32 abs(s32);
extern u8 town_map_trigger_handler[];


/* Trigger an action and update the object state when either position limit is exceeded. */
void trigger_action_when_position_limit_exceeded(S_800C1F8C_0 *object)
{
    s32 x_offset;
    s32 y_offset;
    s32 x_distance;
    s32 y_distance;

    x_offset = object->x - view_reference_entity.x.w.i;
    x_distance = abs(x_offset);
    y_offset = object->y - view_reference_entity.y.w.i;
    y_distance = abs(y_offset);
    if (object->reset_limit_x >= (s16)x_distance && object->reset_limit_y >= (s16)y_distance) {
        return;
    }
    SD_Call(object->argument | 0x1000);
    object->handler = (map_trigger_callback_fn)town_map_trigger_handler;
}
