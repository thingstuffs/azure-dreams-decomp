#include "common.h"

#include "common.h"

extern void func_80034F88(void *arg0, s32 arg1);
extern s32 func_80034FD0(void *arg0);
extern void func_800350D4(void *arg0);
extern void func_80037D9C(void *arg0, s32 arg1);

void func_80035164(void *arg0, s32 arg1, s32 arg2)
{
    s32 selector;

    if (func_80034FD0(arg0) != 0) {
        if (*(u8 *)arg0 != 0) {
            func_800350D4(arg0);
            func_80037D9C(arg0, (u8)arg2);
        } else {
            selector = arg2 & 0xFF;
            if (*((u8 *)arg0 + 2) == selector) {
                goto finish;
            }
            func_800350D4(arg0);
            func_80037D9C(arg0, selector);
        }
    } else {
        func_80037D9C(arg0, (u8)arg2);
    }
finish:
    func_80034F88(arg0, arg1);
}
