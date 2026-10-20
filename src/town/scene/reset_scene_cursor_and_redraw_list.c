#include "common.h"

/* Devkit link-at-0 image C copy of the scene-step routine reset_cursor_and_redraw_list (src/town/func_80881424.c);
 * the latched length (0xD9C) and the redraw argument (0xDA0) are separate words here. */
extern s32 D_00000D9C;
extern s32 D_00000DA0;
extern void func_800007F0(s32);
extern s32 select_first_unmet_table_entry(void);
extern void pass_pair_table_values(void);
extern void set_up_town_resolves_record(s32, s32);

/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 reset_scene_cursor_and_redraw_list(void) {
    s32 list_length;

    func_800007F0(0);
    pass_pair_table_values();
    list_length = select_first_unmet_table_entry();
    D_00000D9C = list_length;
    set_up_town_resolves_record(list_length, D_00000DA0);
    return D_00000D9C;
}
