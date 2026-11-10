#include "town/scene.h"
#include "common.h"
#include "town.h"


/* Forward the context and request to apply_selected_entry_values. */
void forward_context_request_to_handler_e(void *context, s32 request) {
    apply_selected_entry_values(context, request);
}
