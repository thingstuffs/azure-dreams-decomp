/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"
#include "town/event/state.h"


extern s32 town_object_resource_table[];
extern s32 D_800D0690[];
extern s32 D_800D0710[];
extern s32 D_800F8C80[];

/*
 * Sets state data D_800F8C80 and object data D_800D0710, initializes the town resource table
 * entries, and binds optional state D_800D0690.
 */
void initialize_object_resources_and_state(void *object, void *init_arg, SpriteFrameState *state) {
    state->source = D_800F8C80;
    *(void **)((u8 *)object + 0x7C) = D_800D0710;
    handle_insert_initialize_two_values_status_flags(object, init_arg, town_object_resource_table);
    initialize_optional_object_state(object, init_arg, state, D_800D0690);
}
