#ifndef TOWN_SHOP_TARGET_POSITION_DATA_H
#define TOWN_SHOP_TARGET_POSITION_DATA_H

#include "common.h"

/* Three fixed-point position words at 0x80100B50. The writer fills the
 * coordinate halves of the first two words and the full Z word. */
typedef struct TownOutput {
    u32 first;
    u32 second;
    u32 third;
} TownOutput;

extern TownOutput shop_target_position;

#endif
