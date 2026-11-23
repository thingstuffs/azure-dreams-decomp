#include "common.h"
#include "town/scene/entry_requests.h"
#include "town.h"
#include "town/scene.h"

/* Forward the object and entry index to func_80017A48. */
void forward_scene_entry_index_c(TownObjectSet *object, s32 entry_index) {
    process_checked_entry(object, entry_index);
}
