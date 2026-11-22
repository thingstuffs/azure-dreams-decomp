#include "common.h"
#include "shared/entity_objects.h"

#include "town/map/trigger_callbacks.h"
#include "sdk/libc.h"
#include "slus.h"

/* Trigger an action and update the object state when either position limit is exceeded. */
void rearm_trigger_when_player_leaves(map_trigger_record *object)
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
    object->handler = trigger_entity_action_when_allowed;
}
