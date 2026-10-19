#include "common.h"
extern u8 D_800A0000[];

extern s32 D_804094E8;
extern s32 D_804094EC;
extern s32 D_80409500;
extern s32 D_8009E390[];

extern void func_80401578(void);
extern s32 func_80408644(s32 slot_selector);
extern s32 func_80408684(s32 slot_selector);

/* Processes the selection selection_state and clears the selected slot on completion. */
s32 process_selection(void)
{
    s32 selection_state;
    s32 return_code;
    s32 *selected_slot;

    selection_state = D_804094E8;
    return_code = 0;
    if (selection_state != 0) {
        switch (selection_state) {
        case 1:
            func_80401578();
            if ((func_80408684(D_804094EC) != 0) &&
                ((func_80408644(D_804094EC != 0) & 4) != 0)) {
                D_80409500 = selection_state;
                D_804094E8 = D_804094E8 + 1;
                break;
            }
            D_804094E8 = 0;
            return_code = 5;
            break;
        case 3:
            selected_slot = (s32 *)D_800A0000 - 1820;
            if (D_804094EC != 0) {
                selected_slot++;
            }
            return_code = 3;
            *selected_slot = 0;
            D_804094E8 = 0;
            break;
        default:
            return_code = 5;
            break;
        }
    }
    return return_code;
}
