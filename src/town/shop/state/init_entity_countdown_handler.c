#include "common.h"
#include "shared/object_node.h"


   /* arg2 in init_entity_countdown_handler */

#include "town/menu/window.h"
#include "shared/position_views.h"
#include "town/shop.h"
#include "town/shop/state.h"
void invoke_entity_callback_and_follow_up(func_800A06C8_EntityLike *entity, s32 callback_id, SpriteFrameState *callback_data);
typedef struct S_8009ECF0_0 S_8009ECF0_0;

/* Clear the state fields and initialize the record handlers and mode. */
void init_entity_countdown_handler(TownObjectRecord *record_data, TownObjectRecord *state, MotionDeltaView *values) {
    state->unk_15 = 0;
    values->velocity_x = 0;
    values->velocity_y = 0;
    values->velocity_z = 0;
    record_data->unk_50.as_pm = &update_entity_until_countdown_ends;
    record_data->timer = 7;
    NODE_HEADER(record_data)->update_callback = &invoke_entity_callback_and_follow_up;
}
