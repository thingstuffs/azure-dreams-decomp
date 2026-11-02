#include "common.h"
#include "town/map.h"
#include "town/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* came_bright_set: Set camera brightness. */
void came_bright_set(u32 brightness) {
    *view_gray_command = brightness;
}
