#include "common.h"

extern void func_80016B88(void);
extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04(u8 *, s32, s32);
extern s32 *func_80019ABC(u8 *, s32 *, s32, s32);
extern s32 func_8001A510(s32);

extern s32 D_8001A974;
extern s32 D_8001B1FC;
extern s32 D_8001B63C;
extern s32 D_8001B6D0;
extern s32 D_8001B824;
extern s32 D_8001C5FB;
extern s32 D_8001C64E;

s32 *func_80016C00(s32 arg0, s32 arg1, s32 arg2) {
    u8 *page_v0;
    u8 *var_s0;
    s32 *var_s1;

    if (arg2 == 9) {
        if (func_80017E98(arg0, arg1) != 0) {
            if (func_8001A510(0x798) != 0) {
                page_v0 = (u8 *)0x80020000;
                ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                return (s32 *)(page_v0 - 0x4930);
            }
            if (func_8001A510(0x47D) == 0) {
                page_v0 = (u8 *)0x80020000;
                ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                return (s32 *)(page_v0 - 0x49C4);
            }
        }
        var_s0 = (u8 *)0x80020000;
        ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        var_s0 -= 0x568C;
        var_s1 = func_80019ABC(var_s0, &D_8001B1FC, arg0, arg2);
        if (func_80019A04(var_s0, arg0, arg2) != 0) {
            page_v0 = (u8 *)0x80020000;
            ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            var_s1 = (s32 *)(page_v0 - 0x39B2);
        }
    } else if (arg2 == 1) {
        page_v0 = (u8 *)0x80020000;
        ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_s1 = (s32 *)(page_v0 - 0x47DC);
    } else {
        func_80016B88();
        page_v0 = (u8 *)0x80020000;
        ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_s1 = (s32 *)(page_v0 - 0x3A05);
    }
    return var_s1;
}

/* MECHANISM: The true-space three-argument ABI yields the exact 0x28 frame and s3/s2 holds.
   A guarded s0 page live range splits the base across predecessor delay slots and the merge.
   Guarded v0 page returns split each address across branch and epilogue-jump delay slots.
   Nested fallthrough removes the two-word branch-displacement cascade from the explicit goto. */
