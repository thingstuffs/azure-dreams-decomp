#include "common.h"

/* --- gcc 2.7.2 -O2 -fno-expensive-optimizations translation unit --- */

extern char D_80080B88[12];
extern char D_80080B90[12];
extern void func_800508F0();
extern void func_800499E8();

/* Initializes the sub-objects at offsets 0 and 0x18 from shared templates. */
void func_8005097C(char *object)
{
    char *base = object;
    func_800508F0(base, D_80080B88);
    func_800499E8(base + 0x18, D_80080B88, D_80080B90);
}
