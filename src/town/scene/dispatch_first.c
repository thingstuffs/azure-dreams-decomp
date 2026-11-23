#include "common.h"
#include "town/scene/dispatch.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

extern s32 D_8001B8F8[];

/* Dispatch the first and third arguments using the fixed data tables. */
s32 dispatch_first(TownObjectSet *dispatch_value, s32 unused, s32 dispatch_option) {
    return apply_entry_position(D_8001B8F8, scene_dispatch_context, dispatch_value, dispatch_option);
}
