#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "town/event.h"

/* Returns without performing any work. */
void no_op_action_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
}
