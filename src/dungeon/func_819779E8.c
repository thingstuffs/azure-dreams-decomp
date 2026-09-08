#include "common.h"

typedef struct S_800251E8_0_pre {
    u16 unk_00;
} S_800251E8_0_pre;   /* the 0x2 bytes before object in func_800251E8, addressed as object[-1] */

typedef struct S_800251E8_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u16 unk_08;
} S_800251E8_0;   /* object in func_800251E8 */

typedef struct S_800251E8_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_800251E8_1;   /* linked in func_800251E8 */



extern void *D_80024008[];
extern s32 D_800814A0[3];

typedef struct LoopEntry {
    u8 pad0[0xA];
    u16 fieldA;
    u8 padC[0x3A];
    u16 field46;
    u8 pad48[0x3A];
    s16 field82;
} LoopEntry;

void func_800251E8(void *arg0)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4
    };
    void *object;
    S_800251E8_1 *linked;
    s32 state;
    s32 condition;
    s32 i;
    u32 offset;
    u16 value46;
    u16 loop_amount;
    u16 valueA;
    s32 value82;
    s32 adjusted82;

    object = arg0;
    linked = ((S_800251E8_0 *)object)->unk_00;
    linked->unk_1A++;
    ((S_800251E8_0 *)object)->unk_06.s++;
    state = ((S_800251E8_0 *)object)->unk_04.s;
    if ((u32)state >= 5U) {
        goto loop_init;
    }
    (void)jt_keep;
    goto *D_80024008[state];

jt_c0:
    ((S_800251E8_0 *)object)->unk_08 -= 0xC0;
    if (((S_800251E8_0 *)object)->unk_06.u < 8) {
        goto loop_init;
    }
    goto reset_state;

jt_c1:
    condition = ((S_800251E8_0 *)object)->unk_06.u < 12;
    goto shared_test;

jt_c2:
    condition = ((S_800251E8_0 *)object)->unk_06.u < 4;
    goto shared_test;

jt_c3:
    condition = ((S_800251E8_0 *)object)->unk_06.u < 8;

shared_test:
    i = 0;
    if (condition) {
        goto loop_body;
    }

reset_state:
    ((S_800251E8_0 *)object)->unk_06.s = 0;
    ((S_800251E8_0 *)object)->unk_04.u++;
    goto loop_init;

jt_c4:
    ((S_800251E8_0_pre *)object)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    return;

loop_init:
    i = 0;

loop_body:
    offset = 0;
    do {
        value46 = ((u16 *)object)[offset + 0x23];
        loop_amount = ((S_800251E8_0 *)object)->unk_08;
        valueA = ((u16 *)object)[offset + 5];
        valueA++;
        ((u16 *)object)[offset + 0x23] = value46 + loop_amount;
        valueA += i / 6;
        ((u16 *)object)[offset + 5] = valueA;
        if (i >= 6) {
            value82 = ((s16 *)object)[offset + 0x41];
            if (i < 24) {
                adjusted82 = value82 + 5;
                adjusted82 -= i;
            } else {
                adjusted82 = value82 - 19;
            }
            ((s16 *)object)[offset + 0x41] = adjusted82;
        }
        i++;
        offset++;
    } while (i < 30);

    return;
}
