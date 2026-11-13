#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position.h"

#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */
#include "shared/sprite_frame_state.h"


/* Advance the object's position and handle crossing the sampled limit. */
void advance_player_position(TownObjectRecord *context, ObjectPosition *object, SpriteFrameState *sprite) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->velocity_z);
    limit = query_capped_surface_height(object, &position_query_scratch);
    if (limit < object->z.w.i) {
        set_height_and_slope_velocity((object), limit, (struct TownVec * *)(&position_query_scratch));
        initialize_record_with_handler_table(context, (object), sprite);
        return;
    }
    add_vertical_gravity(object);
}
