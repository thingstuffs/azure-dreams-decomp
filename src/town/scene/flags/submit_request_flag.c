#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern M2C_UNK D_800189A4;
extern M2C_UNK scene_event_lookup_context;

/* Submit the request with the shared data when its flag is clear. */
void submit_request_flag(s32 request_id, s32 unused, s32 flag_id) {
    if (get_special_data_for_low_value_id(flag_id) == 0) {
        apply_entry_position(&D_800189A4, &scene_event_lookup_context, request_id, flag_id);
    }
}
