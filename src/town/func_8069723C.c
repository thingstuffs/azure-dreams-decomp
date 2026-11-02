#include "common.h"
#include "town/scene/entry_requests.h"
#include "town.h"

/* Forward an object and its entry index to func_80017A48. */
void forward_scene_entry_index_a(void *object, s32 entry_index) {
    process_checked_entry(object, entry_index);
}
