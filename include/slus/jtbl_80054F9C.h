#ifndef SLUS_JTBL_80054F9C_H
#define SLUS_JTBL_80054F9C_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/sound_state.h"
#include "common.h"

/* Task/timer object struct, shared with w_800559B4.c's SoundTask (field0 is a
 * callback function pointer; field8/fieldA/field18 are s16). */

/* Activates the task, snapshots its timer on entry, and assigns the pad event priority. */

void func_80054F9C(s32 pad_event, SoundTask *task);

#endif
