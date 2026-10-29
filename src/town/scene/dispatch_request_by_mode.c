#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"
#include "town/shop.h"

extern ScenePositionEntry D_8001BB4C[];
extern s32 scene_dispatch_context;
extern s32 D_8001FAE8[];

/* Processes a request by mode, returning a fallback pointer if the mode 7 check fails. */
s32 dispatch_request_by_mode(void *request, s32 unused, s32 mode) {
    void *saved_request = request;
    s32 saved_mode;
    ScenePositionEntry *data_base;
    s32 result;

    saved_mode = mode;
    data_base = D_8001BB4C;
    result = apply_entry_position(data_base, &scene_dispatch_context, saved_request, saved_mode);
    if (saved_mode == 7) {
        if (count_free_item_slots() != 0) {
            return result;
        }
        return (s32)D_8001FAE8;
    }
    resolve_entry_flag(data_base, saved_request, saved_mode);
    return result;
}
