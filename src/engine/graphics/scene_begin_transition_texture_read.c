#include "common.h"
#include "engine/graphics.h"
#include "slus.h"
#include "slus/data.h"

/*
 * Clears the task state and registers task 6 and its follow-up callback.
 *
 * opaque global buffer registered as a task/timer entry; size unknown but must be >8 bytes to
 * force %hi/%lo addressing (matches gp-vs-hilo rule)
 */
void scene_begin_transition_texture_read(unsigned char *task_state)
{
    *task_state = 0;
    Control_CD(6, transition_texture_resource, 0);
    Control_CD(0xFF, set_byte_one, task_state);
}
