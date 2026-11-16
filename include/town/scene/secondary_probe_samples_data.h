#ifndef TOWN_SCENE_SECONDARY_PROBE_SAMPLES_DATA_H
#define TOWN_SCENE_SECONDARY_PROBE_SAMPLES_DATA_H

#include "common.h"

/* Six 16-byte probe offsets in the block at 0x800D0348. */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} TownProbeSample;

extern TownProbeSample *town_secondary_probe_samples;

#endif
