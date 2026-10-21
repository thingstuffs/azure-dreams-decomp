#include "common.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

/* Control_CD(kind, callback, arg) - registers a callback in some table */

/* Clears the state byte and registers two callbacks, binding the default handler to it. */
void scene_begin_transition_data_read(u8 *state)
{
    *state = 0;
    Control_CD(6, &transition_data_resource, 0);
    Control_CD(0xFF, set_byte_one, state);
}
