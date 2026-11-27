#include "slus/jtbl_80054F9C.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "engine/audio.h"

/* Sets a sound task to state 2 and chooses its priority from the event byte. */
void set_sound_task_priority(s32 pad_event, SoundTask *task) {
    u32 event_index;
    s32 priority;

    if (task->fade_mode != 2) {
        task->fade_target = task->fade_level;
        task->fade_mode = 2;
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
    task->fade_out_step = priority;
}
