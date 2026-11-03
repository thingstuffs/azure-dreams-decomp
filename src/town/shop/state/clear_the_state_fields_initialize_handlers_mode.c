#include "common.h"


   /* arg2 in clear_the_state_fields_initialize_handlers_mode */

#include "town/menu/window.h"
#include "shared/position_views.h"
#include "town/shop.h"
#include "town/shop/state.h"
void invoke_entity_callback_and_follow_up(func_800A06C8_EntityLike *entity, s32 callback_id, SpriteFrameState *callback_data);
typedef struct S_8009ECF0_0 S_8009ECF0_0;

/* Clear the state fields and initialize the record handlers and mode. */
void clear_the_state_fields_initialize_handlers_mode(TownObjectRecord *record_data, TownObjectRecord *state, MotionDeltaView *values) {
    state->unk_15 = 0;
    values->velocity_x = 0;
    values->velocity_y = 0;
    values->velocity_z = 0;
    record_data->unk_50.as_pm = &run_both_updates_decrement_countdown_check_completion;
    record_data->timer.as_s16 = 7;
    ((ObjectNodeHeader *)record_data - 1)->update_callback = &invoke_entity_callback_and_follow_up;
}
