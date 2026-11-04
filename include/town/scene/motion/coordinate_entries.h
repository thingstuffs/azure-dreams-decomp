#ifndef TOWN_SCENE_MOTION_COORDINATE_ENTRIES_H
#define TOWN_SCENE_MOTION_COORDINATE_ENTRIES_H

#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

UA32 *copy_and_terminate_coordinate_entries(UA32 *buffer);

#endif
