#include "common.h"

extern void func_8004B364(int a0, int a1, int a2, int a3);

/* Forwards two values to func_8004B364 with two leading zero arguments. */
void func_8004B404(int value, int unused_1, int unused_2, int extra_value)
{
    int saved_value = value;
    value = 0;
    func_8004B364(value, value, saved_value, extra_value);
}


/* Fixed input buffers and the shared texture-result pointer. */
extern u8 D_80016000[0x10];
extern u8 D_80023000[0x10];
extern void *D_8008152C;

extern void func_800479D4(void *a0, void *a1, u16 a2);

/* Registers callbacks for the fixed buffers and returns the result-pointer slot. */
void *func_80047DB8(s32 id)
{
    func_800479D4(&D_80016000, &D_80023000, (u16)id);
    return &D_8008152C;
}
