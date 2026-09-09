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
    s32 value;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    object = D_800E3DF0[((S_800956B8_0 *)arg3)->unk_03 & 0x1F];
    if (!(((S_800956B8_1 *)object)->unk_1C & 0x20000)) {
        result = func_800A1BD0(object);
        /* Retail callee sets a3 = 10 at 0x80099114 before reading it; no incoming argument. */
        arg0 = func_800990FC();
        {
            register u8 *msg3 ASM_REG("$4"); /* MATCH: materialize each shared message address directly in a0. */
            if (result >= 0) {
                u8 *msg;
                value = func_80099194(D_800E0B18, (s32)arg0);
                if (result != 0) {
                    u8 *page;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    page = (u8 *)0x800E0000;
                    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    msg = page + 0x5F0;
                } else {
                    u8 *page;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    page = (u8 *)0x800E0000;
                    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    msg = page + 0x5E1;
                       /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                }
                tail_result = func_80099194(msg, value);
                msg3 = D_800E0B2B;
                value = tail_result - 3;
            } else {
                msg3 = D_800E202D;

                   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                value = (s32)arg0;
                   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            }
            value = func_80099194(msg3, value);
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80099290(value);
        }
        func_800A5720((s32)arg0);
        return;
    }

    index = (s16)func_800A1C14(object);
    if (index >= 0) {
        object = ((S_800956B8_2 *)((u8 *)arg0 + index * 4))->unk_AC;
        if (((S_800956B8_1 *)object)->unk_14 & 0x20000000) {
            ((S_800956B8_1 *)object)->unk_1C |= 0x10000;
            func_800ACB98(object, ((S_800956B8_1_pre *)object)[-1].unk_00,
                         ((S_800956B8_1_pre *)object)[-1].unk_04, object);
            return;
        }
    }

    index = func_800A1BD0(object);
    {
        void *st;
        register s32 two ASM_REG("$2"); /* MATCH: retain retail's v0 literal and v1 state pointer in the shared tail. */

        if (index >= 0) {
            void *tail_selected;
            tail_selected = ((S_800956B8_2 *)((u8 *)arg0 + index * 4))->unk_AC;
            st = tail_selected;
            two = 2;
        } else {
            st = ((Rec_func_8008D024_arg0 *)arg0)->unk_60;
            two = 2;
        }
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
