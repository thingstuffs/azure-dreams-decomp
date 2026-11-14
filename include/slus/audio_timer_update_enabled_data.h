#ifndef SLUS_AUDIO_TIMER_UPDATE_ENABLED_DATA_H
#define SLUS_AUDIO_TIMER_UPDATE_ENABLED_DATA_H

#include "common.h"

/* The timer-update enable flag at 0x80073824 is one word. Padding retains
 * retail hi/lo addressing in the two functions that access it. */
typedef struct AudioTimerUpdateEnabled {
    s32 value;
    s32 pad[2];
} AudioTimerUpdateEnabled;

extern AudioTimerUpdateEnabled audio_timer_update_enabled;

#endif
