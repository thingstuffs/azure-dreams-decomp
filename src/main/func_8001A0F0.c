#include "common.h"

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
        status = 5;
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
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        completion_flag = (s32 *)0x800A0000;
        ASM_KEEP_NV(completion_flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        completion_flag = (s32 *)((u8 *)completion_flag - 0x1C70);
        ASM_KEEP_NV(completion_flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (selected_slot != 0) {
            completion_flag++;
        }
        status = 2;
        ASM_KEEP_NV(status);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        {
            register s32 flag_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            flag_value = 1;
            *completion_flag = flag_value;
        }
        D_804094E8 = 0;
        return status;
    }

five_exit:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
done:
    return status;
}
