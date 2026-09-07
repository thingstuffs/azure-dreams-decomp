#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
extern void func_80027A08() __attribute__((noreturn));
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

    input_word = FIELD(input, s32, 8);
    if (input_word == 0) {
        return;
    }

    flags = FIELD(input, volatile s32, 0x10);
    if (flags & 0x20) {
        func_80053DA8(0x515);
        FIELD(arg0, M2C_UNK *, -0x10) = &D_80027E10;
        FIELD(arg0, s32, 0) = FIELD(arg0, s32, 4);
        func_80028620((u8 *)arg0 - 0x20);
        func_80025598(FIELD(arg0, s32, 0x44));
        func_80027A08();
        return;
    }

    if (flags & 0x10) {
        func_80053DA8(0x503);
        func_800274A8(arg0);
        func_800255AC(FIELD(arg0, s32, 0x44));
        func_80027A08();
        return;
    }

    if (flags & 0x40) {
        func_80053DA8(0x503);
        func_80027454((u8 *)arg0 + 0x38, FIELD(arg0, s32, 0x14),
                     (FIELD(arg0, s32, 8) / 72) * 72,
                     FIELD(arg0, s32, 0x28));
        func_8002661C(func_8002553C(FIELD(arg0, s32, 0x44)),
                     FIELD(arg0, s32, 0x40) +
                         (FIELD(arg0, s32, 8) % 72) * 2);
        func_80027A08();
        return;
    }

    if (!(input_word & 0x5000)) {
        goto check_delta;
    }

    if (flags & 0x5000) {
        FIELD(arg0, s32, 0xC) = 0;
        flags = FIELD(input, volatile s32, 0x10);
        if (flags & 0x1000) {
            goto dispatch_negative;
        }
        tail_flags = flags & 0x4000;
        ASM_KEEP(tail_flags);
        func_80027954(input_word, input);
        return;
    }

    counter = FIELD(arg0, s32, 0xC);
    if (counter < 9) {
        goto increment_count;
    }

    FIELD(arg0, s32, 0xC) = counter - 1;
    flags = FIELD(input, volatile s32, 8);
    if (!(flags & 0x1000)) {
        goto test_positive;
    }

dispatch_negative:
    delta = -9;
    ASM_TAILSLOT_PIN(delta);
    func_80027968(input_word, input);
    return;

test_positive:
    if (!(flags & 0x4000)) {
        goto check_delta;
    }

dispatch_positive:
    delta = 9;
    ASM_TAILSLOT_PIN(delta);
    func_80027968(input_word, input);
    return;

increment_count:
    FIELD(arg0, s32, 0xC) = counter + 1;

check_delta:
    if (delta == 0) {
        return;
    }

    func_80053DA8(0x502);
    new_pos = FIELD(arg0, s32, 8) + delta;
    limit = FIELD(arg0, s32, 0x3C);
    remaining = limit - new_pos / 9;
    if (remaining <= 0 || limit < remaining) {
        return;
    }

    old_pos = new_pos - delta;
    FIELD(arg0, s32, 8) = new_pos;
    if (new_pos / 72 != old_pos / 72) {
        func_80026CD8(FIELD(arg0, s32, 0x88));
        FIELD(arg0, M2C_UNK *, -0x10) = &D_80027E84;
        FIELD(arg0, s32, 0) = FIELD(arg0, s32, 4);
        func_80027A08();
        return;
    }

    func_80026D0C(FIELD(arg0, s32, 0x88));
}

/* MECHANISM: cdk-G0 gives the retail 0x20 frame and held D_80083160 base in a1.
   A volatile input+8 reread restores the two-word CSE gap; a distinct kept tail_flags
   fills word 90 in v0, while LEAD28 sinks the dead s0=-9/+9 values into tail-j slots. */
