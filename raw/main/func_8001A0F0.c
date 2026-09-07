#include "common.h"

extern s32 D_804094E8;
extern s32 D_804094EC;
extern s32 D_80409500;
extern s32 D_8009E390[];

extern void func_804014E4(void);
extern s32 func_80408644(s32 arg0);
extern s32 func_80408674(s32 arg0);

s32 func_804010F0(void) {
    s32 result;
    u32 *destination_one;
    s32 *destination_three;
    s32 selection;
    u32 state;

    state = D_804094E8;
    result = 0;
    if ((state != 0) && (state != 2)) {
        if (state < 3U) {
            if (state == 1) {
                goto state_one;
            }
            result = 5;
            goto done;
        }
        if (state == 3) {
            goto state_three;
        }
        result = 5;
        goto five_exit;

state_one:
        destination_one = &D_8009E390[0];
        if (D_804094EC != 0) {
            destination_one = &D_8009E390[1];
        }
        if (*destination_one != 0) {
            D_804094E8 = 0;
            result = 1;
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
        selection = D_804094EC;
        ASM_SCHED_BARRIER();
        destination_three = (s32 *)0x800A0000;
        ASM_KEEP_NV(destination_three);
        destination_three = (s32 *)((u8 *)destination_three - 0x1C70);
        ASM_KEEP_NV(destination_three);
        if (selection != 0) {
            destination_three++;
        }
        result = 2;
        ASM_KEEP_NV(result);
        {
            register s32 store_value ASM_REG("$2");
            store_value = 1;
            ASM_KEEP_NV(store_value);
            *destination_three = store_value;
        }
        D_804094E8 = 0;
        return result;
    }

five_exit:
    ASM_SCHED_BARRIER();
done:
    return result;
}
