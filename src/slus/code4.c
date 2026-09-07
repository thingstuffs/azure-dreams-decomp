#include "common.h"

/* --- gcc 2.7.2 -O2 -fno-expensive-optimizations translation unit --- */

/* Initializes the sub-object at a0 (func_800508F0, templated off D_80080B88) and
 * the following sub-object at a0+0x18 (func_800499E8, off D_80080B88/D_80080B90). */
extern char D_80080B88[12];
extern char D_80080B90[12];
extern void func_800508F0();
extern void func_800499E8();

void func_8005097C(char *a0)
{
    char *s0 = a0;
    func_800508F0(s0, D_80080B88);
    func_800499E8(s0 + 0x18, D_80080B88, D_80080B90);
}
