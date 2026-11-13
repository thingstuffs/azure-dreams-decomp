#ifndef SLUS_AUDIO_MASTER_LEVEL_H
#define SLUS_AUDIO_MASTER_LEVEL_H

#include "common.h"

typedef struct S_80073738 {
    u16 f0;
    s16 pad[7];
} S_80073738;

extern S_80073738 audio_master_level;

#endif
