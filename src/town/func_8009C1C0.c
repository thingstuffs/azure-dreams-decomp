/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/person/position.h"

/* Refreshes height and steps positive Y until the countdown becomes negative, then resets the handler. */
void step_actor_positive_y_until_timer_expires(Rec_func_80094268_arg0 *state, EntityRec *object, s32 context) {
    u16 ticks_left;

    object->z.w.i = query_lowered_transform_position(object);
    ticks_left = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_record_with_handler_table((Struct8009B1C8 *)(state), (s32)(object), context);
        return;
    }
    object->y.v = (s32) (object->y.v + 0x20000);
}
