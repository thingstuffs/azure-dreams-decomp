#include "common.h"

extern s32 D_804094E8;
extern s32 D_804094EC;
extern s32 D_80409500;
extern s32 D_8009E390[];

extern void func_80401578(void);
extern s32 func_80408644(s32 arg0);
extern s32 func_80408684(s32 arg0);

s32 func_804012B0(void)
{
    s32 state;
    register s32 result ASM_REG("$17");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 selection;
    s32 *destination;

    state = D_804094E8;
    result = 0;
    if (state == 0) goto done;
    if (state == 1) goto case_one;
    if (state == 3) goto case_three;
    result = 5;
    goto done;

case_one:
    func_80401578();
    if ((func_80408684(D_804094EC) != 0) &&
        ((func_80408644(D_804094EC != 0) & 4) != 0)) {
        D_80409500 = state;
        D_804094E8 = D_804094E8 + 1;
        goto fast_done;
    }
    D_804094E8 = 0;
    result = 5;
    goto done;

case_three:
    selection = D_804094EC;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    destination = (s32 *)0x800A0000;
    ASM_KEEP(destination);   /* MATCH pin: load-bearing for the whole function shape */
    destination -= 1820;
    ASM_KEEP(destination);   /* MATCH pin: load-bearing for the whole function shape */
    if (selection != 0) {
        destination++;
        result = 3;
    } else {
        result = 3;
    }
    *destination = 0;
    D_804094E8 = 0;
    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
    goto fast_done;

done:
    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
fast_done:
    return result;
}
