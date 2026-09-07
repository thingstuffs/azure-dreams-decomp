#include "common.h"

extern void func_80021B18(void *arg0, s32 arg1);
extern s32 func_80021C4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80021DF4(s32 arg0, void *arg1);
extern void func_80021EB8(void *arg0);
extern void func_800220DC(void);
extern void rename(void *arg0, void *arg1);

extern s32 D_80083E98[][32];

s32 func_80021F18(s32 arg0, void *arg1) {
    s32 sp18[8];
    s32 sp38[8];
    s32 *base;
    s32 *temp_s1;
    s32 temp_v0;

    func_80021B18(sp18, arg0);
    func_80021B18(sp38, 5);
    base = (s32 *)&D_80083E98;
    temp_s1 = (s32 *)((u8 *)base + (arg0 << 7));
    if (*temp_s1 != 0) {
        rename(sp18, sp38);
    }
    *(s32 *)((u8 *)arg1 + 0x204) = 0;
    func_80021EB8(arg1);
    temp_v0 = func_80021C4C(sp38, arg1, 0xC0, 0, *temp_s1);
    if (temp_v0 != 0) {
        func_80021DF4(arg0, arg1);
        func_800220DC();
    }
    rename(sp38, sp18);
    return temp_v0;
}
