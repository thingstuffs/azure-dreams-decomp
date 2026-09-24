#include "common.h"

/* S_80081480: >8B struct forced to hi/lo addressing (only field0 @ offset 0 accessed here) */
extern s32 D_80081480;

/* S_8008148C: >8B struct forced to hi/lo addressing (only field0 @ offset 0 accessed here) */
extern s32 D_8008148C;

extern void func_80040A88(int a0);
extern void func_80041AE4(void);

/* Copy the value from D_8008148C to D_80081480 and register func_80041AE4. */
void func_80041AB0(void) {
    D_80081480 = D_8008148C;
    func_80040A88((int)func_80041AE4);
}
