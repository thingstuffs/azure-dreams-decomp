#include "common.h"

extern s32 func_80017E98(void);
extern s32 func_80019A04(void *, void *, s32);
extern s32 func_80019ABC(void *, void *, void *, s32);
extern s32 func_8001A510(s16);

extern s32 D_8001A99C;
extern s32 D_8001B1F8;
extern s32 D_8001B208;
extern s8 D_8001B7AE;
extern s8 D_8001EDD0;
extern s8 D_8001EF6C;
extern s8 D_8001F543;

s32 func_80017214(void *arg0, s32 arg1, s32 arg2)
{
    void *base;
    s32 result;
    s32 ret;

    if (func_80017E98() != 0) {
        s32 page;

        page = (s32)0x80020000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        return page - 0x4852;
    }

    base = &D_8001A99C;
    result = func_80019ABC(base, &D_8001B1F8, arg0, arg2);
    ret = result;
    if (func_80019A04(base, arg0, arg2) != 0) {
        if (func_8001A510(*(s16 *)((s8 *)arg0 + 0x18)) != 0) {
            s32 page;

            page = (s32)0x80020000;
            ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
            ret = page - 0xABD;
        } else {
            u8 *state_page;

            state_page = (u8 *)0x80020000;
            ASM_KEEP(state_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            if (*(s32 *)(state_page - 0x4DF8) == 0) {
                s32 zero_page;

                *(s32 *)(state_page - 0x4DF8) = 1;
                zero_page = (s32)0x80020000;
                ASM_KEEP(zero_page);   /* MATCH pin: load-bearing for the whole function shape */
                ret = zero_page - 0x1094;
            } else {
                s32 nonzero_page;

                nonzero_page = (s32)0x80020000;
                ASM_KEEP(nonzero_page);   /* MATCH pin: load-bearing for the whole function shape */
                ret = nonzero_page - 0x1230;
            }
        }
    }
    return ret;
}

/* MECHANISM: The true-space three-argument ABI gives the 0x28 frame and s2/s3 argument holds;
   a held D_8001A99C base uses s0 and the first call result stays in s1.
   Guarded v0 page carriers split address construction across branch/jump delay slots.
   Split zero/nonzero v0 names plus a pinned v1 state page preserve the tail load/store CFG. */
