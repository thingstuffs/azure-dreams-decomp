#include "common.h"

typedef struct S_800251F0_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    u16 unk_0A;
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    u8 pad_0E[0x10];
    u16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x62];
    u16 unk_8C;
} S_800251F0_0;   /* arg1 in func_800251F0 */

typedef struct S_800251F0_1 {
    u8 pad_00[0x6428];
    s16 unk_6428;
} S_800251F0_1;   /* page in func_800251F0 */



extern void *D_80024028[8];
extern s32 D_800814A0;
extern void func_80025328(void) __attribute__((noreturn));

void func_800251F0(void *arg0)
{
    static void *const jt_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_2,
        &&case_2, &&case_2, &&case_2, &&case_2
    };
    register u8 *page ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *arg1;
    u16 old_counter;
    s32 i;

    arg1 = arg0;
    page = (u8 *)0x80020000;
    ASM_KEEP(page);   /* MATCH pin: retail delay-slot fill depends on it */
    old_counter = ((S_800251F0_0 *)arg1)->unk_02.s;
    ((S_800251F0_1 *)page)->unk_6428 = 1;
    ((S_800251F0_0 *)arg1)->unk_02.s = old_counter - 1;
    ((S_800251F0_0 *)arg1)->unk_8C += 200;
    ((S_800251F0_0 *)arg1)->unk_0A++;
    if ((s16)((S_800251F0_0 *)arg1)->unk_0A < 2) {
        goto counter_done;
    }
    ((S_800251F0_0 *)arg1)->unk_0A = 0;
    ((S_800251F0_0 *)arg1)->unk_0C.s++;
counter_done:
    if (((S_800251F0_0 *)arg1)->unk_0C.u >= 33) {
        ((S_800251F0_0 *)arg1)->unk_0C.u = 32;
    }

    i = 0;
    while (i < ((S_800251F0_0 *)arg1)->unk_0C.u) {
        u8 *elem;

        elem = arg1 + i;
        elem[0x50] += 2;
        i++;
    }

    {
        s32 state;

        state = *(s16 *)(arg1 + 0x1E);
        if ((u32)state >= 8) {
            goto done;
        }
        (void)jt_keep;
        goto *D_80024028[(u32)state];
    }

case_0:
    ((S_800251F0_0 *)arg1)->unk_1E++;
    ((S_800251F0_0 *)arg1)->unk_28 += 0x10;
    func_80025328();
    return;

case_1:
    ((S_800251F0_0 *)arg1)->unk_1E++;
    ((S_800251F0_0 *)arg1)->unk_28 -= 0x30;
    ((S_800251F0_0 *)arg1)->unk_29 += 0x20;
    func_80025328();
    return;

case_2:
    ((S_800251F0_0 *)arg1)->unk_28 -= 0x30;
    ((S_800251F0_0 *)arg1)->unk_29 -= 0x20;
    ((S_800251F0_0 *)arg1)->unk_1E = 0;

done:
    if (((S_800251F0_0 *)arg1)->unk_02.u <= 0) {
        (*(u16 *)((u8 *)arg1 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
