/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void dev_report_kind_mode_sno();                     /* extern */
void shop_dispatch_entry_value();                     /* extern */
s32 shop_find_first_eligible_entry();                                /* extern */
void shop_process_entry_pairs();                            /* extern */
s32 shop_check_selected_entry_state();                             /* extern */
void shop_update_availability_flag();                            /* extern */
M2C_UNK func_80702924();                         /* extern */
void reset_town_display_pick_scene();                    /* extern */

extern s32 D_80701DC4_0[];
extern s32 D_80701DC4_1[];
extern s32 D_80701DC4_2[];
extern s32 D_80701DC4_3[];
extern s32 D_80701DC8_0[];
extern s32 D_80701DC8_1[];

/* Run the shop's open sequence and return the resulting handle. */
s32 shop_run_open_sequence(void) {
    s32 handle;

    shop_dispatch_entry_value(0);
    dev_report_kind_mode_sno(0);
    shop_process_entry_pairs();
    handle = shop_find_first_eligible_entry();
    D_80701DC4_0[0] = handle;
    D_80701DC8_0[0] = shop_check_selected_entry_state(handle);
    shop_update_availability_flag();
    dev_report_kind_mode_sno(0);
    reset_town_display_pick_scene(D_80701DC4_1[0], D_80701DC8_1[0]);
    func_80702924(D_80701DC4_2[0]);
    return D_80701DC4_3[0];
}
