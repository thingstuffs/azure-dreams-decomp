#include "common.h"

/* External word holding the current buffer write position. */
extern s32 D_80081480;

/* External word holding the buffer base. */
extern s32 D_8008148C;

extern void func_80040A88(int a0);
extern void func_80041AE4(void);

/* Copy the value from D_8008148C to D_80081480 and register func_80041AE4. */
void func_80041AB0(void) {
    D_80081480 = D_8008148C;
    func_80040A88((int)func_80041AE4);
}
