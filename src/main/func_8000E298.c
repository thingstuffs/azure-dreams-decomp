#include "common.h"

extern s32 D_800287C8;
extern s32 D_800287CC;
extern s32 D_800287E0;
extern s32 D_80084118[];

extern void func_80021538(void);
extern s32 func_80069C18(s32 arg0);
extern s32 func_80069C38(s32 arg0);

s32 func_80021298(void)
{
    s32 state;
    s32 result;

    state = D_800287C8;
    result = 0;
    if (state == 0) {
        goto done;
    }
    if (state == 1) {
        goto state_one;
    }
    result = 5;
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_one:
    func_80021538();
    if (func_80069C38(D_800287CC) != 0) {
        if ((func_80069C18(D_800287CC != 0) & 4) != 0) {
            D_800287E0 = state;
            D_800287C8++;
            goto done;
        }
        result = 5;
        D_800287C8 = 0;
        goto done;
    }
    result = 5;
    D_800287C8 = 0;
    goto done;

state_three:
    {
        s32 *value;

        value = &D_80084118[0];
        if (D_800287CC != 0) {
            value = &D_80084118[1];
        }
        result = 3;
        *value = 0;
        D_800287C8 = 0;
        ASM_SCHED_BARRIER();
    }

done:
    return result;
}
