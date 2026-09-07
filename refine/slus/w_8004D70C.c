#include "common.h"

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

/* Processes two dispatch-slot pairs, then rebuilds matrices. */
void func_8004D70C(void)
{
    struct S_8004D70C_D80083160 *dispatch_table = &D_80083160;
    func_8004D690(&dispatch_table->f_CC, &dispatch_table->f_110, 0);
    func_8004D690(&dispatch_table->f_154, &dispatch_table->f_198, 1);
    func_8004D4AC();
}
