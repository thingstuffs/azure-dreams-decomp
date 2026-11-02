#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "town/map/animation.h"
#include "engine/node.h"
#include "town/map.h"



/* town_rain_in: creates a rain object with its callback, preset values, and position. */
void town_rain_in(s16 x, s16 y) {
    u16 preset_value;
    TownMapSpawnState *state;
    ObjectNodeHeader *object;

    object = allocate_list_node(2, &scene_object_list_anchor.next);
    if (object != 0) {
        object->update_callback = spawn_randomized_timed_objects;
        ((TownMapSpawnState *)(object + 1))->origin_x = ((u16)view_reference_entity.x.w.i);
        state = (TownMapSpawnState *)(object + 1);
        state->origin_y = ((u16)view_reference_entity.y.w.i);
        preset_value = ((u16)view_reference_entity.z.w.i);
        state->base_y = x;
        state->span_y = y;
        state->count = 6;
        state->origin_z = preset_value;
    }
}
