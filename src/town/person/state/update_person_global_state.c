#include "common.h"
#include "town/person.h"
#include "town/person/state.h"
#include "town/event/saved_motion_data.h"

extern s32 scene_object_payload_alias;
extern u8 town_input_motion_address[];
extern u16 D_80100D62;

/* Copy global state into the object and values, then conditionally call set_person_velocity_from_angle. */
void update_person_global_state(void *object, s32 call_arg, s32 *values) {
    u16 saved_value = D_80100D62;
    IntVector3 *saved_values = town_saved_motion_pointer;

    *(u16 *)((u8 *)object + 0x72) = saved_value;
    if (saved_values != 0) {
        values[0] = saved_values->x;
        values[1] = saved_values->y;
        values[2] = saved_values->z;
    }

    if (scene_object_payload_alias != (s32)town_input_motion_address) {
        set_person_velocity_from_angle(object, call_arg, values);
    }
}
