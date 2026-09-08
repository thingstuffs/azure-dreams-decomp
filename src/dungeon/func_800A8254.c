#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern s16 func_8009FD40(void *, void *);
extern void func_800A9A0C(void *, void *);
extern void func_800AAA28(void *, void *);
extern s16 func_800B500C(u8, u8, s16);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern DungeonEntry D_800E3648[];


typedef struct S_800AD9B4_0_pre {
    u16 unk_00;
} S_800AD9B4_0_pre;   /* the 0x2 bytes before arg1 in func_800AD9B4, addressed as arg1[-1] */


typedef struct S_800AD9B4_1 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_800AD9B4_1;   /* base in func_800AD9B4 */


typedef struct S_800AD9B4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_800AD9B4_3;   /* state in func_800AD9B4 */

s32 func_800AD9B4(Rec_D_80082E80 *arg0, void *arg1)
{
    u8 *base;
    u8 *state;
    DungeonEntry *table;
    register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 index;
    s32 result;
    s8 amount;

    if (((S_800AD9B4_0_pre *)arg1)[-1].unk_00 & 0x8000) {
        goto tail;
    }
    page = (u8 *)0x80080000;
    ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
    base = page + 0x2E80;
    ASM_KEEP(base);   /* MATCH pin: load-bearing for the whole function shape */
    if (((S_800AD9B4_1 *)base)->unk_26 == arg0->unk_26.as_s8) {
        goto body;
    }
    if (func_8009FD40(base, arg0) < 7) {
        goto body;
    }

tail:
    return 1;

body:
    if (((Rec_D_800E3D7C *)arg1)->unk_24.at01_u8.v == 0) {
        goto tail;
    }

    index = func_800B500C(arg0->unk_24,
                          arg0->unk_25,
                          ((Rec_D_800E3D7C *)arg1)->unk_88.as_s16);
    ASM_KEEP(index);   /* MATCH pin: keeps a statement from moving across a call/branch */
    result = 1;
    if (index >= 0) {
        table = D_800E3648;
        ASM_KEEP(table);   /* MATCH pin: retail delay-slot fill depends on it */
        if (!(table[index].flags & 0x80)) {
            goto tail;
        }

        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        state = page + 0x3460;
        ASM_KEEP(state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (((S_800AD9B4_3 *)state)->unk_02 & 0x1000) {
            amount = ((Rec_D_800E3D7C *)arg1)->unk_71.as_s8;
            if (amount > 0) {
                ((S_800AD9B4_3 *)state)->unk_08 =
                    ((S_800AD9B4_3 *)state)->unk_08 -
                    (amount - ((Rec_D_800E3D7C *)arg1)->unk_8A.as_u16);
                ((Rec_D_800E3D7C *)arg1)->unk_71.as_s8 = 0;
            }
        }

        func_800A9A0C(arg1, state);
        func_800AAA28(arg0, arg1);
        result = 0;
    }
    return result;
}

/* MECHANISM: The 0x20 frame follows from holding arg1 in s0 and arg0 in s1.
   Dispatcher-first CFG plus a v1 signed index fixes branch and return-value roles.
   Kept table/state bases and a v0 0x8008 page split reproduce address emission order. */
