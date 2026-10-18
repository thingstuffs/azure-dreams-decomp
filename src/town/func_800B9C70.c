#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_building_region_resources();                            /* extern */

/* Updates the active entries through initialize_building_region_resources. */
void update_active_building_entries(void) {
    initialize_building_region_resources();
}
