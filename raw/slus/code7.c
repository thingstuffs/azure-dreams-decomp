#include "common.h"

/* --- gcc 2.8.1 -O2 -fno-schedule-insns2 translation unit --- */

/* Forwards (0, 0, a0, a3) to func_8004B364 (a0 saved before being zeroed).
   maspsx LEAD 1b un-fills the jr load-delay slot with the sp restore. */
extern void func_8004B364(int a0, int a1, int a2, int a3);

void func_8004B404(int a0, int a1, int a2, int a3)
{
    int save = a0;
    a0 = 0;
    func_8004B364(a0, a0, save, a3);
}


/* Regular (>8B) globals accessed via %hi/%lo. */
extern u8 D_80016000[0x10];
extern u8 D_80023000[0x10];
extern u8 D_8008152C[0x10];

extern void func_800479D4(void *a0, void *a1, u16 a2);

/* Passes fixed globals plus the truncated argument through to func_800479D4,
   then returns a pointer to a fixed global (its own return value is unused). */
void *func_80047DB8(s32 a0)
{
    func_800479D4(&D_80016000, &D_80023000, (u16)a0);
    return &D_8008152C;
}
