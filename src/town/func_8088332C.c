#include "common.h"

/* Copy of the devkit scene step reset_cursor_and_redraw_list (src/town/func_80881424.c) in the image linked at
 * file 0x802800; here the latched length (0x8070070C) and the redraw argument (0x80700710) are separate words. */

extern s32 D_8070070C;
extern s32 D_80700710;
extern void func_80700894(s32);
extern s32 func_80700A78(void);
extern void process_pair_16_bit_table(void);
extern void redraw_devkit_list_and_rekey_rows(s32, s32);

/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 copy_devkit_scene_step_reset(void) {
    s32 list_length;

    func_80700894(0);
    process_pair_16_bit_table();
    list_length = func_80700A78();
    D_8070070C = list_length;
    redraw_devkit_list_and_rekey_rows(list_length, D_80700710);
    return D_8070070C;
}
