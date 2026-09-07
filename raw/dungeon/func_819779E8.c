#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80024008[];
extern s32 D_800814A0[3];
extern void func_80025338(void) __attribute__((noreturn));

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
    void *linked;
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
    linked = FIELD(object, void *, 0);
    FIELD(linked, u16, 0x1A)++;
    FIELD(object, u16, 6)++;
    state = FIELD(object, s16, 4);
    if ((u32)state >= 5U) {
        goto loop_init;
    }
    (void)jt_keep;
    goto *D_80024008[state];

jt_c0:
    FIELD(object, u16, 8) -= 0xC0;
    if (FIELD(object, s16, 6) < 8) {
        goto loop_init;
    }
    goto reset_state;

jt_c1:
    condition = FIELD(object, s16, 6) < 12;
    goto shared_test;

jt_c2:
    condition = FIELD(object, s16, 6) < 4;
    goto shared_test;

jt_c3:
    condition = FIELD(object, s16, 6) < 8;

shared_test:
    i = 0;
    if (condition) {
        goto loop_body;
    }

reset_state:
    FIELD(object, u16, 6) = 0;
    FIELD(object, u16, 4)++;
    goto loop_init;

jt_c4:
    FIELD(object, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    func_80025338();

loop_init:
    i = 0;

loop_body:
    offset = 0;
    do {
        value46 = ((u16 *)object)[offset + 0x23];
        loop_amount = FIELD(object, u16, 8);
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
