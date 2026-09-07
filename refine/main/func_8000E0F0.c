#include "common.h"

extern s32 D_800287C8;
extern s32 D_800287CC;
extern s32 D_800287E0;
extern s32 D_80084118[];

extern s32 func_80069C18(s32 arg0);
extern s32 func_80069C08(s32 arg0);
extern void func_800214A4(void);

/* Advance the selected entry through its completion states and return its status. */
s32 func_800210F0(void)
{
    s32 state;
    s32 result;

    state = D_800287C8;
    result = 0;
    if (state == 0 || state == 2) {
        goto done;
    }
    if ((u32)state < 3) {
        if (state == 1) {
            goto state_one;
        }
        result = 5;
        goto done;
    }
    result = 5;
    if (state == 3) {
        goto state_three;
    }
    goto return_result;

state_one:
    {
        s32 *completion_flag;

        completion_flag = &D_80084118[0];
        if (D_800287CC != 0) {
            completion_flag = &D_80084118[1];
        }
        if (*completion_flag != 0) {
            result = 1;
            D_800287C8 = 0;
            goto done;
        }
        if ((func_80069C18(0) & 1) == 0 &&
            (func_80069C18(1) & 1) == 0) {
            goto return_result;
        }
        func_800214A4();
        do {
            state = func_80069C08(D_800287CC);
        } while (state == 0);
        D_800287E0 = 0;
        D_800287C8 = 3;
        goto done;
    }

state_three:
    {
        s32 *completion_flag;

        completion_flag = &D_80084118[0];
        if (D_800287CC != 0) {
            completion_flag = &D_80084118[1];
        }
        result = 2;
        *completion_flag = 1;
        D_800287C8 = 0;
        ASM_CLOBBER("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    }

done:
    return result;
return_result:
    return result;
}
