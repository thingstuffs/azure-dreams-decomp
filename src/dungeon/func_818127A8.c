#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800277A8_0 {
    u8 pad_00[0x8];
    union { s32 s; volatile s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    volatile s32 unk_10;
} S_800277A8_0;   /* input in func_800277A8 */

typedef struct S_800277A8_1_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800277A8_1_pre;   /* the 0x10 bytes before arg0 in func_800277A8, addressed as arg0[-1] */

typedef struct S_800277A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x10];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    u8 pad_48[0x40];
    s32 unk_88;
} S_800277A8_1;   /* arg0 in func_800277A8 */



extern s32 func_8002553C();
extern M2C_UNK func_80025598();
extern M2C_UNK func_800255AC();
extern M2C_UNK func_8002661C();
extern M2C_UNK func_80026CD8();
extern M2C_UNK func_80026D0C();
extern M2C_UNK func_80027454();
extern M2C_UNK func_800274A8();
extern void func_80027954() __attribute__((noreturn));
extern void func_80027968() __attribute__((noreturn));
extern M2C_UNK func_80028620();
extern M2C_UNK func_80053DA8();

extern M2C_UNK D_80027E10;
extern M2C_UNK D_80027E84;
extern u8 D_80083160[];

void func_800277A8(void *arg0) {
    u8 *input = D_80083160;
    s32 input_word;
    s32 flags;
    s32 delta = 0;
    s32 counter;
    s32 new_pos;
    s32 old_pos;
    s32 limit;
    s32 remaining;
    s32 tail_flags;

    input_word = ((S_800277A8_0 *)input)->unk_08.s;
    if (input_word == 0) {
        return;
    }

    flags = ((S_800277A8_0 *)input)->unk_10;
    if (flags & 0x20) {
        func_80053DA8(0x515);
        ((S_800277A8_1_pre *)arg0)[-1].unk_00 = &D_80027E10;
        ((S_800277A8_1 *)arg0)->unk_00 = ((S_800277A8_1 *)arg0)->unk_04;
        func_80028620((u8 *)arg0 - 0x20);
        func_80025598(((S_800277A8_1 *)arg0)->unk_44);
        return;
    }

    if (flags & 0x10) {
        func_80053DA8(0x503);
        func_800274A8(arg0);
        func_800255AC(((S_800277A8_1 *)arg0)->unk_44);
        return;
    }

    if (flags & 0x40) {
        func_80053DA8(0x503);
        func_80027454((u8 *)arg0 + 0x38, ((S_800277A8_1 *)arg0)->unk_14,
                     (((S_800277A8_1 *)arg0)->unk_08 / 72) * 72,
                     ((S_800277A8_1 *)arg0)->unk_28);
        func_8002661C(func_8002553C(((S_800277A8_1 *)arg0)->unk_44),
                     ((S_800277A8_1 *)arg0)->unk_40 +
                         (((S_800277A8_1 *)arg0)->unk_08 % 72) * 2);
        return;
    }

    if (!(input_word & 0x5000)) {
        goto check_delta;
    }

    if (flags & 0x5000) {
        ((S_800277A8_1 *)arg0)->unk_0C = 0;
        flags = ((S_800277A8_0 *)input)->unk_10;
        if (flags & 0x1000) {
            goto dispatch_negative;
        }
        tail_flags = flags & 0x4000;
        ASM_KEEP(tail_flags);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80027954(input_word, input);
        return;
    }

    counter = ((S_800277A8_1 *)arg0)->unk_0C;
    if (counter < 9) {
        goto increment_count;
    }

    ((S_800277A8_1 *)arg0)->unk_0C = counter - 1;
    flags = ((S_800277A8_0 *)input)->unk_08.u;
    if (!(flags & 0x1000)) {
        goto test_positive;
    }

dispatch_negative:
    delta = -9;
    ASM_TAILSLOT_PIN(delta);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80027968(input_word, input);
    return;

test_positive:
    if (!(flags & 0x4000)) {
        goto check_delta;
    }

dispatch_positive:
    delta = 9;
    ASM_TAILSLOT_PIN(delta);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80027968(input_word, input);
    return;

increment_count:
    ((S_800277A8_1 *)arg0)->unk_0C = counter + 1;

check_delta:
    if (delta == 0) {
        return;
    }

    func_80053DA8(0x502);
    new_pos = ((S_800277A8_1 *)arg0)->unk_08 + delta;
    limit = ((S_800277A8_1 *)arg0)->unk_3C;
    remaining = limit - new_pos / 9;
    if (remaining <= 0 || limit < remaining) {
        return;
    }

    old_pos = new_pos - delta;
    ((S_800277A8_1 *)arg0)->unk_08 = new_pos;
    if (new_pos / 72 != old_pos / 72) {
        func_80026CD8(((S_800277A8_1 *)arg0)->unk_88);
        ((S_800277A8_1_pre *)arg0)[-1].unk_00 = &D_80027E84;
        ((S_800277A8_1 *)arg0)->unk_00 = ((S_800277A8_1 *)arg0)->unk_04;
        return;
    }

    func_80026D0C(((S_800277A8_1 *)arg0)->unk_88);
}

/* MECHANISM: cdk-G0 gives the retail 0x20 frame and held D_80083160 base in a1.
   A volatile input+8 reread restores the two-word CSE gap; a distinct kept tail_flags
   fills word 90 in v0, while LEAD28 sinks the dead s0=-9/+9 values into tail-j slots. */
