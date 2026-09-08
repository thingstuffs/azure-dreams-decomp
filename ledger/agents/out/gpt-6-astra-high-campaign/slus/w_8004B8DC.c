#include "common.h"

extern void func_8004B834(void);
extern void func_8003F320(void);
extern void func_800B6A0C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Forwards five arguments to func_800B6A0C after calling func_8004B834 and func_8003F320. */
void func_8004B8DC(s32 first_arg, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg)
{
    func_8004B834();
    func_8003F320();
    func_800B6A0C(first_arg, second_arg, third_arg, fourth_arg, fifth_arg);
}
