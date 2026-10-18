#include "common.h"
void func_8003D548(s32);                     /* extern */
void func_80400EF8(void);                            /* extern */
extern s8 D_8008CA34;

/* Set the global mode to 2 and invoke the transition routines. */
void func_8001FA74(void) {
    D_8008CA34 = 2;
    func_80400EF8();
    func_8003D548(3);
}
