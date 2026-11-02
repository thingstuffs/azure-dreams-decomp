#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/map/animation.h"
#include "shared/object_node.h"
#include "shared/dungeon_delay_views.h"
#include "engine/node.h"
#include "town/map.h"
#include "town/map/state.h"

   /* arg1 in initialize_object_header_and_state */

/* Initializes an object's header and state, including its associated state value. */
void initialize_object_header_and_state(void *body, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    TownMapPhaseObject *objectState = body;
    ObjectPosition *associatedState = placement;

    ObjectNodeHeader *objectHeader;

    objectHeader = (u8 *)objectState - 0x20;
    objectHeader->update_callback = &update_four_phase_animation;
    register_node(objectHeader, &draw_randomized_white_points);
    objectState->radius_bias = 0x48;
    objectState->phase.s = 0;
    objectState->ticks.s = 0;
    objectState->unk_66 = 0;
    associatedState->z.v = 0xFFA00000;
}
