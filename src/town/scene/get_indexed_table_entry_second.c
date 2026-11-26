#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town.h"
#include "town/scene/component_values_data.h"
#include "town/player.h"

extern s32 *D_80017B6C;

/* Set the active data pointer and process entries for the two checks for index 7. */
void install_table_and_test_entries(void) {
    D_80017B6C = scene_first_component_values;
    if (record_value_table_contains(7) != 0) {
        set_script_flag_bit(F_sbs36_pad08);
    }
    if (town_pair_table_has_first(7) != 0) {
        set_script_flag_bit(F_sbs36_pad07);
    }
}
