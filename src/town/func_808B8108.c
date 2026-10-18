/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s32 D_00003F50;
extern s32 D_00003F54;

M2C_UNK print_scene_sequence_number_sno();                     /* extern */
M2C_UNK dispatch_entry_test_flag_test();                     /* extern */
s32 select_table_entry_zero();                                /* extern */
M2C_UNK process_table_pairs_one_three();                            /* extern */
s32 get_2_flag_flag();                             /* extern */
M2C_UNK update_flag_based_flags();                            /* extern */
M2C_UNK run_setup_and_remap_mode_records();                    /* extern */

/* Captures a value and its associated result, applies both, and returns the stored value. */
s32 capture_apply_and_return_stored_value(void) {
    s32 captured_value;

    dispatch_entry_test_flag_test(0);
    process_table_pairs_one_three();
    captured_value = select_table_entry_zero();
    D_00003F50 = captured_value;
    D_00003F54 = get_2_flag_flag(captured_value);
    update_flag_based_flags();
    print_scene_sequence_number_sno(0);
    run_setup_and_remap_mode_records(D_00003F50, D_00003F54);
    return D_00003F50;
}
