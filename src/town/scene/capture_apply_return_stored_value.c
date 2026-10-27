/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 scene_captured_value;
extern s32 scene_captured_flags;

void print_scene_sequence_number_sno(s32 kind);
void dispatch_entry_test_flag_test(s32 entry_index);
s32 select_table_entry_zero(void);                                /* extern */
void process_table_pairs_one_three(void);
s32 get_2_flag_flag();                             /* extern */ /* Unprototyped: The canonical query takes no arguments; dropping the source operand changes the instruction stream. */
void update_flag_based_flags(void);
void run_setup_and_remap_mode_records(s32 table_index, s32 mode);

/* Captures a value and its associated result, applies both, and returns the stored value. */
s32 capture_apply_and_return_stored_value(void) {
    s32 captured_value;

    dispatch_entry_test_flag_test(0);
    process_table_pairs_one_three();
    captured_value = select_table_entry_zero();
    scene_captured_value = captured_value;
    scene_captured_flags = get_2_flag_flag(captured_value);
    update_flag_based_flags();
    print_scene_sequence_number_sno(0);
    run_setup_and_remap_mode_records(scene_captured_value, scene_captured_flags);
    return scene_captured_value;
}
