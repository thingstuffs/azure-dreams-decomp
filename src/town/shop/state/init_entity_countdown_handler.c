#include "common.h"
#include "shared/object_node.h"


   /* arg2 in init_entity_countdown_handler */

#include "town/menu/window.h"
#include "shared/position_views.h"
#include "town/shop.h"
#include "town/shop/state.h"
typedef struct S_8009ECF0_0 S_8009ECF0_0;

/* Clear the state fields and initialize the record handlers and mode. */
void init_entity_countdown_handler(TownObjectRecord *record_data, TownObjectRecord *state, ObjectPosition *values) {
    state->scene_active = 0;
    values->velocity_x = 0;
    values->velocity_y = 0;
    values->velocity_z = 0;
    record_data->state_callback.as_pm = &update_entity_until_countdown_ends;
    record_data->timer = 7;
    NODE_HEADER(record_data)->update_callback = &invoke_entity_callback_and_follow_up;
}
