#include "common.h"

/* Devkit link-at-0 image C copy of the scene-step routine townResetCursorAndRedrawList (src/town/func_80881424.c);
 * the latched length (0xD9C) and the redraw argument (0xDA0) are separate words here. */
extern s32 D_00000D9C;
extern s32 D_00000DA0;
extern void func_800007F0(s32);
extern s32 func_800009D4(void);
extern void func_80000A30(void);
extern void func_80000CB0(s32, s32);

/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 func_80000A88(void) {
    s32 list_length;

    func_800007F0(0);
    func_80000A30();
    list_length = func_800009D4();
    D_00000D9C = list_length;
    func_80000CB0(list_length, D_00000DA0);
    return D_00000D9C;
}
