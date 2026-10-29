#include "common.h"
#include "town/scene.h"
#include "town/scene/hooks.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Forward the context, value, and options to dispatch_paired_table_values. */
void forward_context_value_options(s32 context, s32 value, s32 options) {
    dispatch_paired_table_values();
}
