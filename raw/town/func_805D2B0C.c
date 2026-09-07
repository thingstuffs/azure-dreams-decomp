#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s8 D_80016000[];
extern s32 D_80019AFC;
extern void *D_80019B90;

extern s32 func_80018504(void);
extern void func_80018934(void);
extern void func_80018D54(void *, u8 *);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);
extern void func_80019638(void);

s32 func_80016B0C(void) {
    u8 local[2];
    void *state;
    register s32 result ASM_REG("$16");
    s32 index;
    u8 *cells;

    ASM_KEEP(result);
    state = *(void **)D_80016000;
    local[0] = 2;
    local[1] = 0xFF;
    index = FIELD(state, s32, 8);
    cells = FIELD(state, u8 *, 0x40);
    D_80019AFC = cells[index * 8 + 4];
    result = func_80018504();

    if (result != 0) {
        if (func_800194D8(0x632) == 0) {
            func_80019458(0x62C);
            func_80019458(0x62D);
        }

        FIELD(
            (u8 *)FIELD(*(void **)D_80016000, u8 *, 0x40)
                + FIELD(*(void **)D_80016000, s32, 8) * 8,
            u8,
            4
        ) = 0;
        D_80019AFC = 0;
        func_80018934();
    } else {
        func_80018D54(D_80019B90, local);
        func_80019638();
    }

    return result;
}

/* MECHANISM: The u8[2] stack buffer yields sp+0x10/+0x11 in the 0x28 frame; direct globals hold the s2/s1 pages.
   A guarded entry $s0 liveness barrier keeps the ra/s2/s1/s0 saves together while result spans both CFG arms.
   The block-local inline cell clear restores retail's v0/v1 coloring, and both paths converge on one epilogue. */
