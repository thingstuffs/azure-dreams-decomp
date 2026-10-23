#include "common.h"
#include "town/scene/entry_requests.h"
#include "shared/town_dispatch_data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800171D8(u8 *entries);

/* Passes D_80018AE8 to func_800171D8. */
void dispatch_scene_entry_table(void) {
    func_800171D8(&D_80018AE8);
}
