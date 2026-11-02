#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern M2C_UNK D_800189BC;
extern M2C_UNK scene_event_lookup_context;
extern M2C_UNK D_8001A04A;

/* Selects a request result and conditionally advances a three-state cursor. */
s32 *select_request_conditionally_three_state(s32 entry_id, s32 unused, s32 request_id) {
    s32 *result;
    s32 cursor;

    result = get_special_data_by_id(request_id);
    if (result != NULL) {
        return result;
    }
    result = apply_entry_position(&D_800189BC, &scene_event_lookup_context, entry_id, request_id);
    cursor = read_script_flag_range(F_sbs34_pad16, 2);
    if (get_script_flag_mask(F_sbs34_pad23) == 0) {
        cursor++;
        if (cursor == 3) {
            cursor = 0;
        }
        write_script_flag_range(F_sbs34_pad16, cursor, 2);
    }
    if ((request_id == 0xB) && (resolve_entry_flag(&D_800189BC, entry_id, 0xB) != 0)) {
        result = &D_8001A04A;
    }
    return result;
}
