#include "common.h"
#include "town/scene/grid_queries.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 apply_selected_entry_values(void *, s32);
/* Forward the context and request to apply_selected_entry_values. */
s32 forward_context_request_to_handler_d(void *context, s32 request) {
    return apply_selected_entry_values(context, request);
}
