#include "common.h"

/* Control_CD(kind, callback, arg) - registers a callback in some table */
extern s32 Control_CD(s32 a0, void *a1, void *a2);
extern void set_byte_one(u8 *a0);
extern u8 D_80071644;

/* Clears the state byte and registers two callbacks, binding the default handler to it. */
void scene_begin_transition_data_read(u8 *state)
{
    *state = 0;
    Control_CD(6, &D_80071644, 0);
    Control_CD(0xFF, set_byte_one, state);
}
