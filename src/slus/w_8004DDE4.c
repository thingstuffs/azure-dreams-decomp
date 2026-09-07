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
    s32 off1;
    s32 off2;
    s32 cb_off;
    s32 *p1;
    s32 *p2;

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

    saved_index = 0x20C11;
    work = D_80081554;
    callback_index = D_80081558;
    off1 = work * 4;
    work += 1;
    cb_off = callback_index * 4;
    p1 = (s32 *)((u8 *)D_80083D98 + off1);
    *p1 = saved_index;
    off2 = work * 4;
    p2 = (s32 *)((u8 *)D_80083D98 + off2);
    saved_index = 1;
    D_80081554 = work;
    work += 1;
    *p2 = saved_index;
    D_80081554 = work;
    func_8003528C((s32 *)((u8 *)D_80083D98 + cb_off));
}
