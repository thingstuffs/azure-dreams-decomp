#include "common.h"
#include "town/map.h"

extern s32 camera_height_mode[3];

/* p_came_set: Set the first camera position component. */
void p_came_set(s32 position) {
    *camera_height_mode = position;
}
