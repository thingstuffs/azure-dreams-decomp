#include "common.h"

typedef struct S_801725B8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801725B8_0;   /* arg0 in func_801725B8 */

typedef struct S_801725B8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_801725B8_1;   /* arg2 in func_801725B8 */

typedef struct S_801725B8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801725B8_2;   /* arg3 in func_801725B8 */

typedef struct S_801725B8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725B8_3;   /* arg1 in func_801725B8 */



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
    switch (((S_801725B8_0 *)arg0)->unk_9B) {
    case 0:
        if (((S_801725B8_1 *)arg2)->unk_14 & 0x8000) {
            ((S_801725B8_0 *)arg0)->unk_9B = 2;
            ((S_801725B8_1 *)arg2)->unk_14 |= 0x6000;
            func_8009C12C(arg3, arg2, ((S_801725B8_2 *)arg3)->unk_2A, 1);
            return;
        }
        {
            u8 *tbl;

            ((S_801725B8_3 *)arg1)->unk_14 = 0;
            ((S_801725B8_3 *)arg1)->unk_10 = 0;
            ((S_801725B8_3 *)arg1)->unk_0C = 0;
            tbl = D_801762E8;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = tbl;
            func_80047784(arg2,
                tbl[((D_80083228 + ((S_801725B8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801725B8_0 *)arg0)->unk_9B++;
        }
        return;

    case 1:
        if (((S_801725B8_1 *)arg2)->unk_04 == 3 && (((S_801725B8_1 *)arg2)->unk_14 & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (!((((S_801725B8_1 *)arg2)->unk_04 == 6 && (((S_801725B8_1 *)arg2)->unk_14 & 0x1000)) ||
              (((S_801725B8_1 *)arg2)->unk_14 & 0xE000))) {
            return;
        }
        func_8009C12C(arg3, arg2, ((S_801725B8_2 *)arg3)->unk_2A, 1);
        ((S_801725B8_0 *)arg0)->unk_9B++;
        /* fallthrough */
    case 2:
        if (!(((S_801725B8_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        func_800AD594(arg3, 0x100);
        ((S_801725B8_0 *)arg0)->unk_8C = &D_80170F20;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A4ACC(arg3);
        return;
    }
}

/* MECHANISM: byte-exact @ 2.8.1-G0. (1) ROWBASE: the six `j 0x8017277C` words
   are this function's OWN epilogue join (0x8017277C is INSIDE the 480-byte
   body at true base 0x801725B8), not calls to an extern func_8017277C as the
   m2c census draft assumed -> plain `return`; that alone took aligned 37 -> 17.
   (2) 3-arm compare-tree switch on ((S_801725B8_0 *)arg0)->unk_9B, case 1 FALLING THROUGH
   into case 2 (retail re-tests 0x14 & 0xE000 after the increment).
   (3) HELD BASE: the table address must live in a `u8 *tbl` local so gcc emits
   `addu`+`lbu 0(reg)`; writing D_801762E8[idx] directly emits a second
   symbol-relative lbu that gas expands via $at (3 words) = the +1 word drift.
   (4) CONFIG: routed 2.7.2-G0 was wrong — the same-idiom sibling func_809A10A8
   is 2.8.1-G0 and so is this row (2.8.0-G0 / 2.7.2-cdk-G0 also match).
   Sibling template: overlays/dungeon/first_pass_matched/func_809A10A8.c. */
