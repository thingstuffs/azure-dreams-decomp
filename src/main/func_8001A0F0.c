#include "common.h"
extern u8 D_800A0000[];

extern s32 D_804094E8;
extern s32 D_804094EC;
extern s32 D_80409500;
extern s32 D_8009E390[];

extern void func_804014E4(void);
extern s32 func_80408644(s32 arg0);
extern s32 func_80408674(s32 arg0);

/* Advances processing for the selected slot and sets its completion flag. */
s32 func_804010F0(void) {
    s32 status;
    u32 *slot_flag;
    s32 *completion_flag;
    s32 selected_slot;
    u32 state;

    state = D_804094E8;
    status = 0;
    if ((state != 0) && (state != 2)) {
        if (state < 3U) {
            if (state == 1) {
                goto state_one;
            }
            status = 5;
            goto done;
        }
        if (state == 3) {
            goto state_three;
        }
        goto five_exit;

state_one:
        slot_flag = &D_8009E390[0];
        if (D_804094EC != 0) {
            slot_flag = &D_8009E390[1];
        }
        if (*slot_flag != 0) {
            D_804094E8 = 0;
            status = 1;
            goto done;
        }
        if (((func_80408644(0) & 1) == 0) &&
            ((func_80408644(1) & 1) == 0)) {
            goto done;
        }
        func_804014E4();
        while (func_80408674(D_804094EC) == 0) {
        }
        D_80409500 = 0;
        D_804094E8 = 3;
        goto done;

state_three:
        selected_slot = D_804094EC;
        completion_flag = (s32 *)D_800A0000;
        completion_flag = (s32 *)((u8 *)completion_flag - 0x1C70);
        if (selected_slot != 0) {
            completion_flag++;
            status = 2;
        } else {
            status = 2;
        }
        {
            s16 flag_value;
            flag_value = 1;
            *completion_flag = flag_value;
        }
        D_804094E8 = 0;
        return status;
    } else {
        goto done;
    }

five_exit:
    status = 5;
done:
    return status;
}
