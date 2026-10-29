#include "common.h"
#include "town/person/object_setup.h"
#include "town/scene/list_setup.h"
#include "town/event/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "engine/menu.h"
#include "town/person.h"
#include "town/scene.h"
#include "town/event/state.h"

extern s32 D_800D0678[];

/* Initializes the state value and sets up the context using D_800D0678. */
void initialize_reaction_context(void *object, void *position, SpriteFrameState *state) {
    state->source = lookup_item_category_mapped_value(4, 1);
    configure_the_set_mode_n_3(object, position, &D_800D0678);
    initialize_optional_object_state(object, position, state, 0);
}
