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
        goto done;

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
        destination_three = &D_8009E390[0];
        if (D_804094EC != 0) {
            destination_three = &D_8009E390[1];
        }
        *destination_three = 1;
        result = 2;
        D_804094E8 = 0;
    }

done:
    return result;
}
