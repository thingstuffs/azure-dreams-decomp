/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

void dev_report_kind_mode_sno(s32 kind);                     /* extern */
void propagate_indexed_flag_pair(s32 entry_index);                     /* extern */
s32 advance_clear_flag_row(void);                                /* extern */
void clear_three_flag_pairs(void);                            /* extern */
s32 get_selected_flag_state(s32 unused_selection);                             /* extern */
void update_combined_flag(void);                            /* extern */
void func_80702924(s32);                         /* extern */
void reset_town_display_pick_scene(s32 scene, s32 mode);                    /* extern */

extern s32 D_80701DC4_0[];
extern s32 D_80701DC4_1[];
extern s32 D_80701DC4_2[];
extern s32 D_80701DC4_3[];
extern s32 D_80701DC8_0[];
extern s32 D_80701DC8_1[];

/* Initialize flag-row selection, report diagnostics, and return the stored word. */
s32 initialize_flag_selection(void) {
    s32 handle;

    propagate_indexed_flag_pair(0);
    dev_report_kind_mode_sno(0);
    clear_three_flag_pairs();
    handle = advance_clear_flag_row();
    D_80701DC4_0[0] = handle;
    D_80701DC8_0[0] = get_selected_flag_state(handle);
    update_combined_flag();
    dev_report_kind_mode_sno(0);
    reset_town_display_pick_scene(D_80701DC4_1[0], D_80701DC8_1[0]);
    func_80702924(D_80701DC4_2[0]);
    return D_80701DC4_3[0];
}
