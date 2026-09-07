#include "common.h"

extern s32 D_80083D98[32];
extern s32 D_80081554;
extern s32 D_80081558;

extern void func_8004DCA8(void *arg);
extern void func_8003528C(void *arg);

void func_8004DDE4(void *arg)
{
    s32 callback_index;
    s32 saved_index;
    s32 initial_index;
    s32 work;
    s32 index;

    index = D_80081554 & 0xF;
    saved_index = index;
    work = 0x15080707;
    D_80081554 = index;
    D_80081558 = saved_index;
    initial_index = index;
    saved_index = work;
    D_80083D98[index] = saved_index;
    D_80081554 = initial_index + 1;
    func_8004DCA8(arg);

    work = D_80081554;
    index = work;
    saved_index = 0x20C11;
    D_80083D98[index] = saved_index;
    work = index + 1;
    D_80081554 = work;
    saved_index = 1;
    D_80083D98[work] = saved_index;
    work += 1;
    D_80081554 = work;
    callback_index = D_80081558;
    func_8003528C(&D_80083D98[callback_index]);
}
