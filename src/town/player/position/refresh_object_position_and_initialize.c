#include "town/player/initialize_record_with_handler_table_api.h"
#include "shared/position_query.h"
#include "common.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position.h"
#include "shared/sprite_frame_state.h"


extern u8 town_actor_control[];

/* Conditionally refreshes object data before passing it to initialize_record_with_handler_table. */
void refresh_object_position_and_initialize(void *context, ObjectPosition *object, SpriteFrameState *sprite) {
    void *state;

    if (town_actor_control[0x3B] != 0) {
        state = *(void **)(*(void **)(town_actor_control + 0x20) + 8);
        if ((*(s32 *)((u8 *)state + 0xC) != 0) ||
            (*(s32 *)((u8 *)state + 0x10) != 0) ||
            (*(s32 *)((u8 *)state + 0x14) != 0)) {
            set_height_and_slope_velocity(object, query_capped_surface_height(object, &position_query_scratch),
                          &position_query_scratch);
        }
    } else {
        set_height_and_slope_velocity(object, query_capped_surface_height(object, &position_query_scratch),
                      &position_query_scratch);
    }
    initialize_record_with_handler_table(context, (object), sprite);
}
