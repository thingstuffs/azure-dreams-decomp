#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern s32 func_8001776C(void);
extern void func_80017E1C(void);
extern void func_80018308(void *, s32);
extern void func_800193E0(s32);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);

extern s8 D_80016000[];
extern s16 D_80019676;
extern s32 D_80019AFC;

s32 func_800167E4(void *arg0, s32 arg1)
{
    void *town;
    s32 id;

    town = *(void **)D_80016000;
    id = FIELD(arg0, s16, 0x18);
    D_80019AFC = FIELD(
        FIELD(town, s32, 8) * 8 + FIELD(town, s32, 0x40),
        u8, 4);

    if (func_800194D8(id) != 0) {
        {
            void *town2;
            s32 index;

            town2 = *(void **)D_80016000;
            index = FIELD(town2, s32, 8);
            FIELD(index * 8 + FIELD(town2, s32, 0x40), s8, 4) = 0;
        }
        id = FIELD(arg0, s16, 0x18);
        D_80019AFC = 0;
        func_80019458(id);
    }

    if (func_8001776C() != 0 && func_800194D8(0x637) != 0) {
        if (func_800194D8(D_80019676) == 0 && D_80019AFC == 0) {
            func_80019458(0x637);
            func_80018308(arg0, arg1);
            return 1;
        }
    } else {
        func_800193E0(0x637);
    }

    func_80017E1C();
    return 0;
}

/* MECHANISM: The true-space function holds the town and status global pages in s1/s0,
   while arg0/arg1 remain live in s2/s3 across calls; an s32 named call argument fixes
   load/store scheduling, and a block-local town2/index scope fixes the v0/v1 coloring. */
