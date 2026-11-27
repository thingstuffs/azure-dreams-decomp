#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/event/object_setup.h"
#include "shared/dungeon_effect_views.h"
#include "town/scene.h"
#include "town/event/state.h"

extern s32 common_object_state_handlers[];


   /* Select a state value and update the record according to its mode flag. */
void select_object_state_by_mode(TownObjectRecord *record, ObjectPosition *context, SpriteFrameState *state, void *default_value,
    void *alternate_value, struct Box *bounds) {
    u8 mode = record->state_index;

    if (mode != 0) {
        state->source = alternate_value;
        init_scene_node_mode_3(record, context, bounds);
        initialize_optional_object_state(record, context, state, 0);
        return;
    }
    state->source = default_value;
    init_scene_list_node(record, context, bounds);
    initialize_optional_object_state(record, context, state, common_object_state_handlers);
}
