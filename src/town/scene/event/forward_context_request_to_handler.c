#include "common.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Forward the context and request to process_checked_entry. */
void forward_context_request_to_handler(void *context, s32 request) {
    process_checked_entry(context, request);
}
