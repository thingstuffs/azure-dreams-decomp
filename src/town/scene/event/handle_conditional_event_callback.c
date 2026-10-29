#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/event.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

typedef struct ScenePositionEntry {
    s16 key;
    s16 selector;
    s32 result;
} ScenePositionEntry;
extern ScenePositionEntry D_8001BE2C[];
extern ScenePositionEntry D_8001BE44[];
extern s16 scene_dispatch_context[];


/* Handles the conditional callback and selects data according to flag 0x1460. */
void handle_conditional_event_callback(s32 context, s32 unused, s32 event_code) {
    void *selected_data;

    if ((event_code == 0x1E) && (check_callback_record_bytes(0xD, 1) != 0)) {
        town_scene_root->services->callback_078(0);
        set_script_flag_bit(Ftt_fkoya_isaku_scene01_ok);
        set_current_entry_script_flag();
    }

    if (get_script_flag_mask(Ftt_fkoya_isaku_scene01_ok) != 0) {
        selected_data = &D_8001BE2C;
    } else {
        selected_data = &D_8001BE44;
    }
    apply_entry_position(selected_data, &scene_dispatch_context, context, event_code);
}
