#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/state_data.h"
#include "town/scene/position_entries.h"
#include "town/scene/flags.h"
#include "town/scene.h"

void decrement_entry_counter_if_flag(void);                            /* extern */
extern ScenePositionEntry D_80018B28;
extern s32 library_lookup_context;

/* Runs the operation and invokes the fallback when both checks return zero. */
s32 apply_scene_entry_and_decrement_counter(TownObjectSet *input, s32 unused, s32 aux_input) {
    s32 result;

    result = apply_entry_position(&D_80018B28, &library_lookup_context, input, aux_input);
    if ((get_script_flag_mask(scene_request_flag_id) == 0) && (resolve_entry_flag(&D_80018B28, input, aux_input) == 0)) {
        decrement_entry_counter_if_flag();
    }
    return result;
}
