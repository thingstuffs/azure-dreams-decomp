#ifndef SLUS_AUDIO_UPDATE_GUARD_DATA_H
#define SLUS_AUDIO_UPDATE_GUARD_DATA_H

#include "common.h"

/* The first word at 0x80085F98 is the audio update guard. The trailing
 * compiler-view padding retains retail hi/lo addressing for its users. */
typedef struct AudioUpdateGuard {
    s32 value;
    s32 pad[3];
} AudioUpdateGuard;

extern AudioUpdateGuard audio_update_guard;

#endif
