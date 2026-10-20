#include "common.h"

extern int Control_CD(int a0, void *a1, void *a2);
extern void set_byte_one(unsigned char *a0);

/* opaque global buffer registered as a task/timer entry; size unknown but
   must be >8 bytes to force %hi/%lo addressing (matches gp-vs-hilo rule) */
extern unsigned char transition_texture_resource[12];

/* Clears the task state and registers task 6 and its follow-up callback. */
void scene_begin_transition_texture_read(unsigned char *task_state)
{
    *task_state = 0;
    Control_CD(6, transition_texture_resource, 0);
    Control_CD(0xFF, set_byte_one, task_state);
}
