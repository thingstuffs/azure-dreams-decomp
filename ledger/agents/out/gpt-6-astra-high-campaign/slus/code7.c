#include "common.h"

/* --- gcc 2.8.1 -O2 -fno-schedule-insns2 translation unit --- */

extern void func_8004B364(int a0, int a1, int a2, int a3);

/* Forwards two values to func_8004B364 with two leading zero arguments. */
void func_8004B404(int value, int unused_1, int unused_2, int extra_value)
{
    int saved_value = value;
    value = 0;
    func_8004B364(value, value, saved_value, extra_value);
}


/* Regular (>8B) globals accessed via %hi/%lo. */
extern u8 D_80016000[0x10];
extern u8 D_80023000[0x10];
extern u8 D_8008152C[0x10];

extern void func_800479D4(void *a0, void *a1, u16 a2);

/* Registers callbacks for the fixed buffers using the id and returns D_8008152C. */
void *func_80047DB8(s32 id)
{
    func_800479D4(&D_80016000, &D_80023000, (u16)id);
    return &D_8008152C;
}
