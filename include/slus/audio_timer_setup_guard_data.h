#ifndef SLUS_AUDIO_TIMER_SETUP_GUARD_DATA_H
#define SLUS_AUDIO_TIMER_SETUP_GUARD_DATA_H

#include "common.h"

/* The first word at 0x800737C0 is the setup guard. Padding retains the
 * retail hi/lo addressing for this large-data compiler view. */
typedef struct AudioTimerSetupGuard {
    s32 value;
    s32 pad[2];
} AudioTimerSetupGuard;

extern AudioTimerSetupGuard audio_timer_setup_guard;

#endif
