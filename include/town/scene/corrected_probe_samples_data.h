#ifndef TOWN_SCENE_CORRECTED_PROBE_SAMPLES_DATA_H
#define TOWN_SCENE_CORRECTED_PROBE_SAMPLES_DATA_H

#include "common.h"

/* Four 16-byte correction offsets in the block at 0x800D0208. */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} Vec4i;

extern Vec4i *town_corrected_probe_samples;

#endif
