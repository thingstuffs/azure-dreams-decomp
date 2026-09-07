#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170F20;
extern u8 D_801762E8[];

void func_801725B8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, u8, 0x9B) = 2;
            FIELD(arg2, u16, 0x14) |= 0x6000;
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
            return;
        }
        {
            u8 *tbl;

            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            tbl = D_801762E8;
            FIELD(arg2, u8 *, 0x2C) = tbl;
            func_80047784(arg2,
                tbl[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, u8, 0x9B)++;
        }
        return;

    case 1:
        if (FIELD(arg2, s8, 0x04) == 3 && (FIELD(arg2, u16, 0x14) & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (!((FIELD(arg2, s8, 0x04) == 6 && (FIELD(arg2, u16, 0x14) & 0x1000)) ||
              (FIELD(arg2, u16, 0x14) & 0xE000))) {
            return;
        }
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg0, u8, 0x9B)++;
        /* fallthrough */
    case 2:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = &D_80170F20;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A4ACC(arg3);
        return;
    }
}

/* MECHANISM: byte-exact @ 2.8.1-G0. (1) ROWBASE: the six `j 0x8017277C` words
   are this function's OWN epilogue join (0x8017277C is INSIDE the 480-byte
   body at true base 0x801725B8), not calls to an extern func_8017277C as the
   m2c census draft assumed -> plain `return`; that alone took aligned 37 -> 17.
   (2) 3-arm compare-tree switch on FIELD(arg0,u8,0x9B), case 1 FALLING THROUGH
   into case 2 (retail re-tests 0x14 & 0xE000 after the increment).
   (3) HELD BASE: the table address must live in a `u8 *tbl` local so gcc emits
   `addu`+`lbu 0(reg)`; writing D_801762E8[idx] directly emits a second
   symbol-relative lbu that gas expands via $at (3 words) = the +1 word drift.
   (4) CONFIG: routed 2.7.2-G0 was wrong — the same-idiom sibling func_809A10A8
   is 2.8.1-G0 and so is this row (2.8.0-G0 / 2.7.2-cdk-G0 also match).
   Sibling template: overlays/dungeon/first_pass_matched/func_809A10A8.c. */
