#include "common.h"
#include "town/map.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 view_gray_command[];
/* came_bright_set: Set camera brightness. */
void came_bright_set(u32 brightness) {
    *view_gray_command = brightness;
}
