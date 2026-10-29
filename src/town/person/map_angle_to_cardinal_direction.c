#include "common.h"
#include "town/person.h"

/* Maps an angle to one of four directions. */
s32 map_angle_to_cardinal_direction(s16 angle) {
    return ((s32) (0x400 - angle) >> 0xA) & 3;
}
