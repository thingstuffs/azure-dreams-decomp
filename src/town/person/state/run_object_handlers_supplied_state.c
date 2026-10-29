#include "common.h"
#include "m2c_compat.h"
#include "town/menu/object.h"
#include "town/person/position.h"
#include "town/person/state.h"

/* Run both object handlers with the supplied state and context. */
void run_object_handlers_supplied_state(s32 object, s32 state, s32 context) {
    create_timed_effect_object(object, state, context);
    move_position_toward_target((void *)(object), (void *)(state), context);
}
