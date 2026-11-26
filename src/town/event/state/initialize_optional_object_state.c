#include "common.h"
#include "town/event/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/town_object.h"
#include "records/Rec_D_80082E80.h"
#include "town/event/object.h"
#include "town/event/state.h"
#include "engine/node.h"
#include "town/event.h"

/* Initialize object and state, using the supplied value or default data. */
void initialize_optional_object_state(void *object_arg, ObjectPosition *context, SpriteFrameState *state, void *init_value) {
    TownObjectRecord *object = object_arg;

    NODE_HEADER(object)->update_callback = dispatch_object_event_or_retire;
    register_node_if_unregistered(object, project_sprite_chain);
    object->unk_8C = 0;
    object->unk_8E = 0;
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->frame_ticks = 0;
    if (init_value != 0) {
        object->state_handlers = init_value;
        select_object_value_by_height_band(object, object, context, state);
        return;
    }
    object->unk_50.as_pm = &noop_hook;
}
