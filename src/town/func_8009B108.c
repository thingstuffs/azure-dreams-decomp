#include "common.h"

extern void copy_motion_parameters_and_reset_flag(s32 record, s32 source);
extern void initialize_record_with_handler_table(s32 record, s32 setup_value, s32 init_value);
extern s32 D_80093D48;
extern s32 *D_800FE5D8;

/* Run both initialization routines and select D_80093D48 as the active data. */
void initialize_record_and_select_active_data(s32 record, s32 setup_value, s32 init_value) {
    copy_motion_parameters_and_reset_flag(record, setup_value);
    initialize_record_with_handler_table(record, setup_value, init_value);
    D_800FE5D8 = &D_80093D48;
}
