#include "script_symbols.h"
#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"
#include "town/scene/flags.h"


extern ScenePositionEntry town_map_selfi_talk_response_entries;
extern u8 town_map_square_flag_override_response;

/* Resolve a table result and apply the conditional override or fallback action. */
s32 select_response_setting_slefy_talk(void *context, s32 unused, s32 entry_key) {
    s32 result;

    result = apply_entry_position(&town_map_selfi_talk_response_entries, active_scene_dispatch_context, context, entry_key);
    if (resolve_entry_flag(&town_map_selfi_talk_response_entries, context, entry_key) != 0) {
        return (s32)&town_map_square_flag_override_response;
    }
    set_script_flag_bit(F_slefy_all_talk_town);
    return result;
}
