#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern s16 scene_request_flag_id;
extern ScenePositionEntry D_80018B00;
extern s32 D_80019A30;
extern s32 D_80019ACC;


/* Prepare request state and select a result buffer based on status checks. */
void *select_response_marking_sbs07_pad21(void *request_id, s32 unused, s32 request_value)
{
    ScenePositionEntry *request_state = &D_80018B00;

    apply_entry_keyed_values(request_state, request_id, request_value);
    if (((get_script_flag_mask(scene_request_flag_id) == 0) &&
         (resolve_entry_flag(request_state, request_id, request_value) == 0)) ||
        (get_script_flag_mask(F_sbs07_pad21) == 0)) {
        set_script_flag_bit(F_sbs07_pad21);
        return &D_80019ACC;
    }
    return &D_80019A30;
}
