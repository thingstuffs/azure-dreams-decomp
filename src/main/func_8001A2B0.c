#include "common.h"

extern s32 D_804094E8;
extern s32 D_804094EC;
extern s32 D_80409500;
extern s32 D_8009E390[];

extern void func_80401578(void);
extern s32 func_80408644(s32 arg0);
extern s32 func_80408684(s32 arg0);

/* Processes the selection selection_state and clears the selected slot on completion. */
s32 func_804012B0(void)
{
    s32 selection_state;
    register s32 return_code ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 selection;
    s32 *selected_slot;

    selection_state = D_804094E8;
    return_code = 0;
    if (selection_state == 0) goto done;
    if (selection_state == 1) goto case_one;
    if (selection_state == 3) goto case_three;
    return_code = 5;
    goto done;

case_one:
    func_80401578();
    if ((func_80408684(D_804094EC) != 0) &&
        ((func_80408644(D_804094EC != 0) & 4) != 0)) {
        D_80409500 = selection_state;
        D_804094E8 = D_804094E8 + 1;
        goto fast_done;
    }
    D_804094E8 = 0;
    return_code = 5;
    goto done;

case_three:
    selection = D_804094EC;
    do {
        selected_slot = (s32 *)0x800A0000;
    } while (0);
    ASM_KEEP(selected_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    selected_slot -= 1820;
    ASM_KEEP(selected_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (selection != 0) {
        selected_slot++;
        return_code = 3;
    } else {
        return_code = 3;
    }
    *selected_slot = 0;
    D_804094E8 = 0;
    goto fast_done;

done:
    ASM_KEEP(return_code);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
fast_done:
    return return_code;
}
