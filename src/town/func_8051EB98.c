#include "common.h"
#include "town/scene/entry_requests.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8001D244[];
/* Returns a pointer to D_8001D244. */
u8 *get_shared_scene_result(void) {
    return D_8001D244;
}
