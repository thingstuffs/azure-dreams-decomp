#include "common.h"

typedef struct S_80025584_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_80025584_0_pre;   /* the 0x10 bytes before arg0 in func_80025584, addressed as arg0[-1] */

typedef struct S_80025584_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
} S_80025584_0;   /* arg0 in func_80025584 */



extern s32 D_80083160[];
extern s32 D_80024FFC;

extern s32 func_8002168C(void);
extern void func_80021904(void);
extern void func_800250E8(void *arg0);
extern void func_800254E4(void *arg0);
extern void func_80025D34(void *arg0);
extern void func_80027AFC(s32 arg0, s32 arg1);
extern s32 func_80049DE8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80053DA8(s32 arg0);

/* Handle menu input, selection repeat, and transition completion. */
void func_80025584(u8 *menu)
{
    s32 selection_delta;
    s32 transition_status;
    s32 repeat_timer;
    s32 buttons;
    s32 *controller;

    controller = D_80083160;
    selection_delta = 0;
    if (controller[2] != 0) {
        if (controller[4] & 0x20) {
            func_80053DA8(0x515);
            ((S_80025584_0_pre *)menu)[-1].unk_00 = &D_80024FFC;
        }
        buttons = controller[4];
        if (buttons & 0x40) {
            func_80053DA8(0x503);
            func_800254E4(menu);
            goto finish_input;
        }
        if (controller[2] & 0x5000) {
            if (buttons & 0x5000) {
                ((S_80025584_0 *)menu)->unk_30 = 0;
                buttons = controller[4];
                if (buttons & 0x1000) {
                    selection_delta = -1;
                } else if (buttons & 0x4000) {
                    selection_delta = 1;
                }
            } else {
                repeat_timer = ((S_80025584_0 *)menu)->unk_30;
                if (repeat_timer >= 13) {
                    ((S_80025584_0 *)menu)->unk_30 = repeat_timer - 2;
                    buttons = controller[2];
                    if (buttons & 0x1000) {
                        selection_delta = -1;
                    } else if (buttons & 0x4000) {
                        selection_delta = 1;
                    }
                } else {
                    ((S_80025584_0 *)menu)->unk_30 = repeat_timer + 1;
                }
            }
        }

finish_input:
        if (selection_delta != 0) {
            func_80053DA8(0x502);
            ((S_80025584_0 *)menu)->unk_28 =
                func_80049DE8(((S_80025584_0 *)menu)->unk_28, selection_delta, 5);
            func_800250E8(menu);
        }
    }

    transition_status = func_8002168C();
    func_80021904();
    if (transition_status == 0) {
        return;
    }
    if (transition_status == 1) {
        return;
    }
    func_80025D34(menu - 0x20);
    func_80027AFC(((S_80025584_0 *)menu)->unk_20, 0);
}
