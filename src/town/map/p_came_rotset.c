#include "common.h"
#include "town/map.h"

extern s32 camera_turn_lock[3];
/* p_came_rotset: Set the first camera rotation component. */
void p_came_rotset(s32 rotation) {
    *camera_turn_lock = rotation;
}
