#include "common.h"
#include "town/scene/dispatch.h"
#include "town/scene/motion.h"

extern s32 D_8001B8F8[];
extern s32 scene_dispatch_context[];

/* Dispatch the first and third arguments using the fixed data tables. */
s32 dispatch_first(s32 dispatch_value, s32 unused, s32 dispatch_option) {
    return apply_entry_position(D_8001B8F8, scene_dispatch_context, dispatch_value, dispatch_option);
}
