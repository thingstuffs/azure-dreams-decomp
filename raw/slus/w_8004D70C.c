#include "common.h"

/* Kicks off the D_80083160 dispatch table: runs func_8004D690 over two
 * dispatch-slot pairs (0xCC/0x110 with index 0, then 0x154/0x198 with
 * index 1; each slot is 0x44 bytes, matching the S_80083178 dispatch-table
 * stride), then calls func_8004D4AC() to rebuild matrices. */
struct S_8004D70C_D80083160 {
    char pad0[0xCC];
    char f_CC[0x44];
    char f_110[0x44];
    char f_154[0x44];
    char f_198[0x44];
};

extern struct S_8004D70C_D80083160 D_80083160;
extern void func_8004D690(void *a0, void *a1, s32 a2);
extern void func_8004D4AC(void);

void func_8004D70C(void)
{
    struct S_8004D70C_D80083160 *base = &D_80083160;
    func_8004D690(&base->f_CC, &base->f_110, 0);
    func_8004D690(&base->f_154, &base->f_198, 1);
    func_8004D4AC();
}
