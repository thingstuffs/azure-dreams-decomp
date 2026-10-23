#include "common.h"
#include "town/scene/entry_requests.h"
void func_80017A48(void *, s32);                            /* extern */

/* Forward the object and entry index to func_80017A48. */
void forward_scene_entry_index_c(void *object, s32 entry_index) {
    func_80017A48(object, entry_index);
}
