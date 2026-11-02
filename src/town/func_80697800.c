#include "common.h"
#include "town/scene/entry_requests.h"
#include "shared/town_dispatch_data.h"
#include "town.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Passes D_80018AE8 to func_800171D8. */
void dispatch_scene_entry_table(void) {
    process_flagged_entries_follow_four(&D_80018AE8);
}
