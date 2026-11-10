#include "common.h"
#include "town/map.h"
#include "town/data.h"

/* came_bright_set: Set camera brightness. */
void came_bright_set(u32 brightness) {
    *view_gray_command = brightness;
}
