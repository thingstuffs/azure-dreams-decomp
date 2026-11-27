#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/event_buffer_data.h"
#include "town/scene/position_entries.h"

extern u8 town_map_state_dependent_response_entries[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

/* Selects an entry pointer, with state-dependent alternatives for entry 0x1E. */
void *select_state_dependent_entry(TownObjectSet *table_index, s32 unused, s32 entry_id) {
    void *result;

    if (entry_id == 0x1E) {
        if (get_script_flag_mask(Ftt_fkoya_isaku_scene00_first) != 0) {
            if (get_script_flag_mask(Ftt_fkoya_isaku_scene00_ok) != 0) {
                result = D_8001E42A;
            } else {
                result = D_8001E16A;
            }
        } else {
            result = scene_event_buffer;
            set_script_flag_bit(Ftt_fkoya_isaku_scene00_first);
        }
    } else {
        result = apply_entry_position(town_map_state_dependent_response_entries, scene_dispatch_context, table_index, entry_id);
    }
    return result;
}
