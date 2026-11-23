#include "common.h"
#include "town/scene/entry_requests.h"
#include "town.h"
#include "town/scene.h"

/* Dispatch an object's indexed entry to the shared handler. */
void forward_scene_entry_index_b(TownObjectSet *object, s32 entry_index) {
    process_checked_entry(object, entry_index);
}
