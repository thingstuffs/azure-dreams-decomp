#include "town/map/camera.h"
#include "town/map/wide_culling_data.h"
#include "town/map/sound_selection_g00648.h"
#include "town/map.h"
#include "town/data.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_800A496C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_func_800A496C_2;

/* Run both contexts' callbacks, then update the flag from the current mode and threshold. */
void run_dual_context_callbacks(void)
{
    TownCameraState *primary_context;
    MapSecondaryCallbackState *secondary_context;
    TownCameraCallback callback;

    primary_context = &town_camera_chase_state;
    secondary_context = &town_secondary_callback_state;

    callback = primary_context->select_target;
    if (callback != NULL) {
        callback(primary_context);
    }
    if (secondary_context->select_title != NULL) {
        secondary_context->select_title((s32 *)secondary_context);
    }
    if (primary_context->track_target != NULL) {
        primary_context->track_target(primary_context);
    }
    if (secondary_context->update_coordinates != NULL) {
        secondary_context->update_coordinates((s32 *)secondary_context);
    }

    update_view_gray_level();
    if (map_scene_selector_alias != 0xC) {
        if (((S_func_800A496C_2 *)D_80100D90)->unk_06 < 0x600) {
            map_wide_culling[0] = 1;
            return;
        }
        map_wide_culling[0] = 0;
    }
}
