#include "town/player/position_handlers.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/player/object.h"
struct TownObj;
struct TownVec;

typedef struct {
    u8 pad0[0xA];
    s16 field_A;
    u8 padC[8];
    s32 field_14;
} TownObject;

/* Updates a town object based on its computed threshold and the global flag. */
void update_airborne_object_until_ground(void *context, ObjectPosition *object, void *update_data)
{
    s16 threshold;
    s32 *threshold_data;

    resolve_collision_axis_order(object);
    store_input_angle(context);
    accelerate_toward_input_keep_speed(object);
    threshold_data = &position_query_scratch;
    threshold = query_capped_surface_height(object, threshold_data);

    if (object->z.w.i >= threshold) {
        set_height_and_slope_velocity(object, threshold, threshold_data);
        initialize_scene_action_record(context, object, update_data);
        return;
    }

    if (town_action_state_flag != 0) {
        object->velocity_z = 0;
        copy_z_to_collision_motion(object);
        initialize_scene_action_record(context, object, update_data);
    } else {
        add_vertical_gravity(object);
    }
}
