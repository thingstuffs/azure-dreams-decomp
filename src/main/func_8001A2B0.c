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
    register s32 result ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    destination = (s32 *)0x800A0000;
    ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    destination -= 1820;
    ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (selection != 0) {
        destination++;
        result = 3;
    } else {
        result = 3;
    }
    *destination = 0;
    D_804094E8 = 0;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    goto fast_done;

done:
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
fast_done:
    return result;
}
