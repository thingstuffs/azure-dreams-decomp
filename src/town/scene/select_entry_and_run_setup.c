#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern s32 scene_captured_value;
extern s32 scene_captured_flags;

s32 select_table_entry_zero(void);                                /* extern */
void process_table_pairs_one_three(void);

/* Captures a value and its associated result, applies both, and returns the stored value. */
s32 select_entry_and_run_setup(void) {
    s32 captured_value;

    update_entry_value_flag_from_test_flag(0);
    process_table_pairs_one_three();
    captured_value = select_table_entry_zero();
    scene_captured_value = captured_value;
    scene_captured_flags = get_selected_flag_stage(captured_value);
    update_combined_flag_from_two_flags();
    print_scene_sequence_number_sno(0);
    load_record_list_by_mode(scene_captured_value, scene_captured_flags);
    return scene_captured_value;
}
