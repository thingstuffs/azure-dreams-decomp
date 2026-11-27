#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

extern u8 D_80019DBC[];
extern u8 theater_position_flag_clear_response[];
extern u8 theater_position_flag_set_response[];
extern u8 D_8001D244[];

/* Selects a result address after checking the object, its position, and state. */
u8 *select_scene_result_address(TownObjectSet *object, s32 check_input_b, s32 check_input_c) {
    const TownFlagDependency *pos;

    if (lookup_with_override_fallback(object, check_input_b, check_input_c) != 0) {
        return D_8001D244;
    }

    pos = object->flag_dependencies;
    update_dependent_entry_ids(pos->source_flag, pos->clear_flag, pos->target_flag);

    if (get_script_flag_mask(F_sbs11_pad30) == 0) {
        set_script_flag_bit(F_sbs11_pad30);
        return D_80019DBC;
    }

    pos = object->flag_dependencies;
    if (get_script_flag_mask(pos->clear_flag) == 0) {
        return theater_position_flag_clear_response;
    }

    return theater_position_flag_set_response;
}
