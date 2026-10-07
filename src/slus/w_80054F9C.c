#include "shared/sound_state.h"
#include "common.h"

/* Task/timer object struct, shared with w_800559B4.c's SoundTask (field0 is a
 * callback function pointer; field8/fieldA/field18 are s16). */

/* Activates the task, snapshots its timer on entry, and assigns the pad event priority. */
void func_80054F9C(s32 pad_event, SoundTask *task) {
    u32 event_index;
    s32 priority;

    if (task->unk_04 != 2) {
        task->unk_0A = task->unk_08;
        task->unk_04 = 2;
    }

    event_index = (pad_event & 0xFF) - 0xB1;
    switch (event_index) {
    case 0:
    case 3:
        priority = 0xF;
        break;
    case 16:
    case 19:
        priority = 4;
        break;
    case 32:
    case 35:
        priority = 2;
        break;
    default:
        priority = 0xA;
        break;
    }
    task->unk_18 = priority;
}
