#include "common.h"

extern void load_bin_nametwin(void);
extern void func_8003F320(void);
extern void func_800B6A0C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Forwards five arguments to func_800B6A0C after calling load_bin_nametwin and func_8003F320. */
void func_8004B8DC(s32 first_arg, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg)
{
    load_bin_nametwin();
    func_8003F320();
    func_800B6A0C(first_arg, second_arg, third_arg, fourth_arg, fifth_arg);
}
