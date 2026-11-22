#include "common.h"
#include "m2c_compat.h"
#include "town/menu/object.h"
#include "town/person/position.h"
#include "town/person/state.h"

/* Run both object handlers with the supplied state and context. */
void run_object_handlers_supplied_state(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    create_timed_effect_object(object, position, sprite);
    move_position_toward_target(object, position, sprite);
}
