#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Return whether the actor script is inactive. */
s32 is_first_entry_field_zero(void) {
    BeldoScriptControl *control = NODE_BODY(beldo_actor_nodes);

    return control->script_active == 0;
}
