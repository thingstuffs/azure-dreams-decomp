#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"
#include "town/player.h"

#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */
#include "shared/sprite_frame_state.h"


/* Update the actor's fall and handle contact with the ground. */
void update_falling_actor_and_handle_ground(TownObjectRecord *context, ObjectPosition *actor, SpriteFrameState *sprite) {
    s16 ground_height;

    ground_height = query_capped_surface_height(actor, &position_query_scratch);
    if (actor->z.w.i >= ground_height) {
        set_height_and_slope_velocity((actor), ground_height, (struct TownVec * *)(&position_query_scratch));
        initialize_record_with_handler_table(context, (actor), sprite);
        return;
    }
    add_vertical_gravity(actor);
}
