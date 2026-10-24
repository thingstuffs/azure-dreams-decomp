#include "common.h"
#include "town/event/mesh_motion.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"
#include "shared/vector.h"


extern u8 town_input_motion_address[];
extern void *town_saved_motion_pointer;


extern IntVector3 D_80100D28;
extern s16 town_motion_x_phase;
extern s16 town_motion_y_phase;
extern s16 town_event_motion_pair[];
extern u8 D_80100D68[];
extern s16 town_motion_x_step;
extern s16 town_motion_y_step;

/* Initializes object state and sets its starting position. */
void initialize_object_state_and_position(void **object, IntVector3 *start_position, void *ptr2) {
        s32 *position;

    call_the_handler_selects_nonzero_entry((s32 *) D_800D0130, (Rec_func_80094268_arg0 *) object, ptr2);
    *object = town_input_motion_address;
    town_orbit_radius = 0;
    town_motion_x_step = 8;
    town_motion_y_step = 8;
    town_motion_x_phase = 0;
    town_motion_y_phase = 0;
    town_mesh_scale = 0;
    town_event_motion_pair[1] = 0;
    town_event_motion_pair[0] = 0;
    D_80100D28.x = start_position->x;
    position = &D_80100D28.x;
    position[1] = start_position->y;
    town_saved_motion_pointer = D_80100D68;
    position[2] = start_position->z;
}
