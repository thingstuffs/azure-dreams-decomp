#include "town/scene/record_actions.h"
#include "town/scene/entry_requests.h"
#include "town/scene/event.h"

s32 forward_context_request_to_handler(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    return process_checked_entry(entry, entry_index);
}
