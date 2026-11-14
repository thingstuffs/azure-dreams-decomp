#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/person/effects.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position_handlers.h"
#include "town/player/object.h"
#include "town/player/position.h"
#include "town/system.h"
struct TownObj;
struct TownVec;

typedef struct TownObject {
    u8 pad0[0xA];
    s16 limit;
    u8 padC[8];
    s32 state;
} TownObject;

#include "town/player/action_initializers.h"

/* Updates a town object based on its table value, limit, and a global flag. */
void update_airborne_object_with_land_effects(void *context, ObjectPosition *object, void *update_arg)
{
    s16 table_value;

    resolve_collision_axis_order(object);
    store_input_angle(context);
    accelerate_toward_input_keep_speed(object);
    table_value = query_capped_surface_height(object, (&position_query_scratch));

    if (object->z.w.i >= table_value) {
        play_overlay_height_sound();
        set_height_and_slope_velocity(object, table_value, (&position_query_scratch));
        spawn_person_radial_effects(object);
        initialize_scene_action_record(context, object, update_arg);
    } else if (town_action_state_flag != 0) {
        play_overlay_height_sound();
        object->velocity_z = 0;
        copy_z_to_collision_motion(object);
        initialize_scene_action_record(context, object, update_arg);
    } else {
        add_vertical_gravity(object);
    }
}
