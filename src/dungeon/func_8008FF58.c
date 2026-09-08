#include "common.h"
#include "records/Rec_func_8008D024_arg0.h"


extern void *D_800E3DF0[];
extern u8 D_800E0B18[16];
extern u8 D_800E0B2B[16];
extern u8 D_800E202D[16];

extern s16 func_800A1BD0(void *arg0);
extern s32 func_800A1C14(void *arg0);
extern void *func_800990FC(void);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80095750(void *arg0, s32 arg1);
extern void func_80095774(void *arg0, s32 arg1);
extern void func_80095828(void);
extern void func_80095838(void);
extern void func_80099290(s32 arg0);
extern void func_800A5720(s32 arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);


typedef struct S_800956B8_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800956B8_0;   /* arg3 in func_800956B8 */

typedef struct S_800956B8_1_pre {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x10];
} S_800956B8_1_pre;   /* the 0x18 bytes before object in func_800956B8, addressed as object[-1] */

typedef struct S_800956B8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_800956B8_1;   /* object in func_800956B8 */

typedef struct S_800956B8_2 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800956B8_2;   /* (u8 *)arg0 + index * 4 in func_800956B8 */


typedef struct S_800956B8_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_800956B8_4;   /* st in func_800956B8 */

void func_800956B8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *object;
    s32 index;
    s32 tail_result;
    s16 result;
    register s32 value ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    object = D_800E3DF0[((S_800956B8_0 *)arg3)->unk_03 & 0x1F];
    if (!(((S_800956B8_1 *)object)->unk_1C & 0x20000)) {
        result = func_800A1BD0(object);
        arg0 = func_800990FC();
        if (result >= 0) {
            value = func_80099194(D_800E0B18, (s32)arg0);
            if (result != 0) {
                register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

                page = (u8 *)0x800E0000;
                ASM_KEEP(page);   /* MATCH pin: keeps a constant in a register as retail does */
                func_80095750(page + 0x5F0, value);
                return;
            } else {
                register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
                u8 *msg;

                page = (u8 *)0x800E0000;
                ASM_KEEP(page);   /* MATCH pin: keeps a constant in a register as retail does */
                msg = page + 0x5E1;
                ASM_USE(msg);   /* MATCH pin: retail keeps a computation the compiler would drop */
                tail_result = func_80099194(msg, value);
                func_80095774(D_800E0B2B, tail_result - 3);
                return;
            }
        } else {
            u8 *msg3 = D_800E202D;

            ASM_USE(msg3);   /* MATCH pin: retail keeps a computation the compiler would drop */
            value = (s32)arg0;
            ASM_USE2(msg3, value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            value = func_80099194(msg3, value);
            ASM_KEEP(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_80099290(value);
        }
        func_800A5720((s32)arg0);
        func_80095838();
        return;
    }

    index = (s16)func_800A1C14(object);
    if (index >= 0) {
        object = ((S_800956B8_2 *)((u8 *)arg0 + index * 4))->unk_AC;
        if (((S_800956B8_1 *)object)->unk_14 & 0x20000000) {
            ((S_800956B8_1 *)object)->unk_1C |= 0x10000;
            func_800ACB98(object, ((S_800956B8_1_pre *)object)[-1].unk_00,
                         ((S_800956B8_1_pre *)object)[-1].unk_04, object);
            func_80095838();
            return;
        }
    }

    index = func_800A1BD0(object);
    if (index >= 0) {
        void *tail_selected;
        register s32 tail_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

        tail_selected = ((S_800956B8_2 *)((u8 *)arg0 + index * 4))->unk_AC;
        tail_value = 2;
        ASM_KEEP(tail_selected);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: load-bearing for the whole function shape */
        func_80095828();
        return;
    }

    {
        void *st;
        register s32 two ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

        st = ((Rec_func_8008D024_arg0 *)arg0)->unk_60;
        two = 2;
        ((S_800956B8_4 *)st)->unk_9A = two;
        ((S_800956B8_4 *)st)->unk_9B = 0;
        ((S_800956B8_4 *)st)->unk_8C = 0;
        ((Rec_func_8008D024_arg0 *)arg0)->unk_110 = arg3;
    }
}

/* MECHANISM: frame is 4 saves (s2,ra,s1,s0 at 0x18/0x1c/0x14/0x10) with arg3->s2
   and arg0->s1; the two message tails take their string address from a $v0-pinned
   page base ((u8*)0x800E0000 + 0x5F0/0x5E1, ASM_KEEP'd) so gcc splits HIGH/LO_SUM
   across two registers instead of coalescing lui+addiu into $a0.  Retail leaves
   both func_80099194 call delay slots EMPTY: the fix is to materialise every arg
   BEFORE a zero-def ASM_USE/ASM_USE2 liveness barrier (a1 pre-set into the $a1-pinned
   `value`), which fences gcc's dbr out of the slot; ASM_USE(msg3) first forces the
   $a0 la ahead of the $a1 move.  The L9 tail wants the loaded state pointer in $v1
   and the literal 2 in $v0 -- plain ASM_REG pins with NO ASM_KEEP (the keep's extra
   DEF reorders the sb/sw group and costs a load-delay nop). */
