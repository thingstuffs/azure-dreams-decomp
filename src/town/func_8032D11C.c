#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void apply_selected_entry_values(void *, s32);
/* Forward the context and request to apply_selected_entry_values. */
void forward_context_request_to_handler_d(void *context, s32 request) {
    apply_selected_entry_values(context, request);
}
