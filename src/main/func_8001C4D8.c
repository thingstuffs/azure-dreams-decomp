#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_804034D8(void *arg0)
{
    s32 stage;
    s32 difference;
    s32 scaled;
    s32 product;
    s32 quotient;
    s32 final_current;
    register u8 *slot ASM_REG("$9");
    register s32 index ASM_REG("$10");
    u32 value;
    u32 next_value;
    u8 stored_value;
    void *cursor4;
    void *cursor1;
    void *node;

    stage = FIELD(arg0, s32, 0x8C);
    difference = FIELD(arg0, s32, 0x88) - stage;
    scaled = FIELD(arg0, s32, 0x84) * 0x10;
    product = difference * scaled;
    quotient = product / FIELD(arg0, s32, 0x80);
    index = 0;
    cursor4 = arg0;
    cursor1 = arg0;
    quotient += 10;
    FIELD(FIELD(FIELD(arg0, void *, 0x1BC), void *, 4), s16, 0xA) =
        stage * 0x10 + quotient;

loop:
    slot = (u8 *)cursor1 + 0x7C;
    value = *slot;
    if (index == FIELD(arg0, s32, 0x88)) {
        s32 tail_numerator;
        s32 tail_denominator;

        tail_numerator = 8;
        tail_denominator = FIELD(arg0, s32, 0x80);
        tail_numerator -= value;
        tail_denominator -= FIELD(arg0, s32, 0x84);
        tail_denominator++;
        quotient = tail_numerator / tail_denominator;
        next_value = value + quotient;
    } else {
        next_value = value;
        if (next_value != 0)
            next_value--;
    }
    *slot = next_value;
    stored_value = FIELD(cursor1, u8, 0x7C);

    FIELD(FIELD(FIELD(cursor4, void *, 0x1E0), void *, 4), s16, 8) =
        stored_value + 0x24;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1F0), void *, 4), s16, 8) =
        stored_value + 0x8F;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1C0), void *, 4), s16, 8) =
        stored_value + 9;
    index++;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1D0), void *, 4), s16, 8) =
        stored_value + 0x42;

    FIELD(FIELD(FIELD(cursor4, void *, 0x1E0), void *, 4), u8, 0) =
        FIELD(cursor1, u8, 0x7C) * 3 + 0x68;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1E0), void *, 4), u8, 1) =
        FIELD(cursor1, u8, 0x7C) * 3 + 0x68;
    node = FIELD(cursor4, void *, 0x1E0);
    cursor4 += 4;
    FIELD(FIELD(node, void *, 4), u8, 2) =
        FIELD(cursor1, u8, 0x7C) * 4 + 0x60;
    cursor1++;
    if (index < 4)
        goto loop;

    final_current = FIELD(arg0, s32, 0x84);
    if (final_current < FIELD(arg0, s32, 0x80))
        FIELD(arg0, s32, 0x84) = final_current + 1;
}
