#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
void check_ready_or_run_followup(s32);                     /* extern */
s32 get_indexed_table_entry(s32 target_value);                         /* extern */
s32 func_80017990(s32 target_value);                         /* extern */
extern M2C_UNK scene_first_component_values;
extern s32 *D_80017B6C;

/* Set the active data pointer and process entries for the two checks for index 7. */
void install_table_and_test_entries(void) {
    D_80017B6C = &scene_first_component_values;
    if (get_indexed_table_entry(7) != 0) {
        check_ready_or_run_followup(F_sbs36_pad08);
    }
    if (func_80017990(7) != 0) {
        check_ready_or_run_followup(F_sbs36_pad07);
    }
}
