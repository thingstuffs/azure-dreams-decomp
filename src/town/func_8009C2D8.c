#include "town/player/motion.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/town_object.h"

#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/person/position.h"
#include "town.h"
#include "shared/sprite_frame_state.h"

/* Refreshes height and steps positive X until the countdown becomes negative, then resets the handler. */
void step_actor_positive_x_until_timer_expires(TownObjectRecord *state, ObjectPosition *object, SpriteFrameState *sprite) {
    u16 ticks_left;

    object->z.w.i = query_lowered_transform_position(object);
    ticks_left = ((u16)state->unk_0A) - 1;
    state->unk_0A = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_record_with_handler_table(state, (object), sprite);
        return;
    }
    object->x.v = (s32) (object->x.v + 0x20000);
}
