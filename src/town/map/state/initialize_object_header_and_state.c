#include "common.h"
#include "town/map/animation.h"
#include "shared/object_node.h"
#include "shared/dungeon_delay_views.h"

s32 register_node();           /* extern */
s32 draw_randomized_white_points(void *first_object, void *first_coords);



   /* arg1 in initialize_object_header_and_state */

/* Initializes an object's header and state, including its associated state value. */
void initialize_object_header_and_state(TownMapPhaseObject *objectState, DelayMotionZ *associatedState) {
    ObjectNodeHeader *objectHeader;

    objectHeader = (u8 *)objectState - 0x20;
    objectHeader->update_callback = &update_four_phase_animation;
    register_node(objectHeader, &draw_randomized_white_points);
    objectState->radius_bias = 0x48;
    objectState->phase.s = 0;
    objectState->ticks.s = 0;
    objectState->unk_66 = 0;
    associatedState->unk_08 = 0xFFA00000;
}
