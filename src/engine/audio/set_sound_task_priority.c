#include "slus/jtbl_80054F9C.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "slus/jtbl_80054F9C.h"
#include "engine/audio.h"

void set_sound_task_priority(s32 pad_event, SoundTask *task) {
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
