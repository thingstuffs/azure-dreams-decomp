#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern u8 D_8001BE24[];
extern u8 scene_dispatch_context[];
extern u8 scene_event_buffer[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

/* Selects an entry pointer, with state-dependent alternatives for entry 0x1E. */
void *select_state_dependent_entry(s32 table_index, s32 unused, s32 entry_id) {
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
        result = apply_entry_position(D_8001BE24, scene_dispatch_context, table_index, entry_id);
    }
    return result;
}
