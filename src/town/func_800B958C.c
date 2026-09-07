#include "common.h"

extern s32 func_80042900(void *, s8);
extern s32 func_800B5E10(s32);
extern void func_800B6D30(void);
extern void func_800B6D40(void);
extern s32 func_80049E88(void *);

s32 func_800B6CEC(void *arg0) {
    s32 temp = *((u8 *) arg0 + 0x13);

    if (temp != 0) {
        if ((func_80042900(arg0, 10) << 0x10) != 0) {
            temp = 47;
            func_800B6D30();
            ASM_KEEP(temp);   /* MATCH pin: retail delay-slot contents depend on it */
            return;
        }
        temp = func_800B5E10(temp);
        ASM_KEEP(temp);   /* MATCH pin: retail delay-slot contents depend on it */
        return temp;
    }
    return func_80049E88(arg0);
}
