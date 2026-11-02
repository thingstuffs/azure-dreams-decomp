#include "common.h"
#include "town/scene/hooks.h"
#include "town/scene.h"

/* Pass the context and entry index to func_80017A48. */
void forward_entry_index(void *context, s32 entry_index) {
    process_checked_entry(context, entry_index);
}
