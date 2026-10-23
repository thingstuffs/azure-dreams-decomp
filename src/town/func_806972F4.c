#include "common.h"
#include "town/scene/entry_requests.h"
void func_80017A48(void *, s32);                            /* extern */

/* Dispatch an object's indexed entry to the shared handler. */
void forward_scene_entry_index_b(void *object, s32 entry_index) {
    func_80017A48(object, entry_index);
}
