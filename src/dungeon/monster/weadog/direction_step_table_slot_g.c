#include "dungeon/monster/weadog.h"

/* Tile offsets indexed by the low three direction bits. */
const GridPoint weadog_slot_g_direction_steps[8] __attribute__((aligned(4))) = {
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { -1, 1 },
    { -1, 0 },
    { -1, -1 },
    { 0, -1 },
    { 1, -1 }
};
