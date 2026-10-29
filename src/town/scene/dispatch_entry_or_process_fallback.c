#include "script_symbols.h"
#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"


extern ScenePositionEntry D_8001BB94;
extern u8 D_8001E891;

/* Resolve a table result and apply the conditional override or fallback action. */
s32 dispatch_entry_or_process_fallback(void *context, s32 unused, s32 entry_key) {
    s32 result;

    result = apply_entry_position(&D_8001BB94, active_scene_dispatch_context, context, entry_key);
    if (resolve_entry_flag(&D_8001BB94, context, entry_key) != 0) {
        return (s32)&D_8001E891;
    }
    set_script_flag_bit(F_slefy_all_talk_town);
    return result;
}
