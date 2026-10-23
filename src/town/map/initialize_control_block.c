#include "common.h"
#include "shared/entity_objects.h"
#include "shared/vector.h"


extern IntVector3 town_position_reference_state;
extern u8 map_control_handler_address[];
extern void initialize_transition_state(void *);

/* Copy the default state and initialize the supplied control block. */
void initialize_control_block(void *control) {
    IntVector3 *dst = &town_position_reference_state;
    s32 value;

    town_position_reference_state.x = view_reference_entity.x.v;
    value = view_reference_entity.y.v;
    dst->z = view_reference_entity.z.v;
    dst->y = value;
    *(void **)((u8 *)control + 0x24) = map_control_handler_address;
    *(s32 *)((u8 *)control + 0x30) = 0;
    initialize_transition_state(control);
}
