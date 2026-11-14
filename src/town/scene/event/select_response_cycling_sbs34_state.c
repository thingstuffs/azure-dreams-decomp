#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/scene/event.h"
#include "town/player/state.h"
#include "town/scene/motion.h"

extern s32 resolve_entry_flag(void *, s32, s32);
extern s32 query_referenced_flag_for_table_entry(void *, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

extern u8 D_80018A0C[16];
extern u8 scene_event_lookup_context[16];
extern u8 D_8001B333[];
extern u8 D_8001B3D2[];

/* Selects a response and advances the four-state counter for event 11. */
s32 select_response_cycling_sbs34_state(s32 context, s32 unused, s32 event_id)
{
    u8 *event_table;
    s32 result;
    s32 state_index;

    if (event_id == 1) {
        return (s32) D_8001B3D2;
    }

    result = get_special_data_for_low_value_id(event_id);
    if (result != 0) {
        return result;
    }

    event_table = D_80018A0C;
    result = apply_entry_position(event_table, scene_event_lookup_context, context, event_id);
    state_index = read_script_flag_range(F_sbs34_pad16, 2);

    if (event_id != 0xB) {
        return result;
    }

    set_script_flag_bit(F_sbs34_pad24);
    if (query_referenced_flag_for_table_entry(event_table, context, 0xB) == 0) {
        if (get_script_flag_mask(F_sbs34_pad23) == 0) {
            state_index++;
            if (state_index == 4) {
                state_index = 0;
            }
            write_script_flag_range(F_sbs34_pad16, state_index, 2);
        }
    }

    if (resolve_entry_flag(D_80018A0C, context, event_id) == 0) {
        return result;
    }
    return (s32) D_8001B333;
}
