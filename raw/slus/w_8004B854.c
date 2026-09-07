#include "common.h"

typedef struct S_8004B854 {
    u8 a2;
    u8 code;
} S_8004B854;

extern void func_8004B834(void);
extern void func_8003F320(void);
extern void func_8002537C(int a0, int a1, int a2, S_8004B854 *a3, int a4);

/* summary: calls func_8004B834(); builds a small stack struct {a2, 0x13} then
   calls func_8002537C(a0, 0, 0, &struct, a1) after calling func_8003F320().
   Note: func_8003F320's return value isn't actually used - v0 happens to hold
   0x13 from the immediately preceding load when it's stored in the delay slot. */
void func_8004B854(int a0, int a1, int a2)
{
    S_8004B854 local;
    int zero = 0;

    func_8004B834();
    local.a2 = (u8)a2;
    local.code = 0x13;
    func_8003F320();
    func_8002537C(a0, zero, zero, &local, a1);
}
