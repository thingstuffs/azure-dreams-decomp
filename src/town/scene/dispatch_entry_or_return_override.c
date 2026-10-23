#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"

extern s32 resolve_entry_flag();
extern s32 apply_entry_position();
extern M2C_UNK D_8001BB7C;
extern u8 D_8001E891;

/* Process the selected entry and return its result or the override pointer. */
s32 dispatch_entry_or_return_override(s32 context, s32 unused, s32 entry_id) {
    s32 entry_result;

    entry_result = apply_entry_position(&D_8001BB7C, active_scene_dispatch_context, context, entry_id);
    return resolve_entry_flag(&D_8001BB7C, context, entry_id) != 0
        ? (s32)&D_8001E891
    : entry_result;
}
