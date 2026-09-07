#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_800232F4(s32 current, s32 value, void *cursor4,
                          void *cursor1);

s32 func_80023258(void *arg0)
{
    s32 stage;
    s32 difference;
    s32 scaled;
    s32 quotient;
    s32 current;
    s32 final_current;
    s32 index;
    register s32 result ASM_REG("$2");
    register u8 *slot ASM_REG("$8");
    s32 value;
    register u8 value2 ASM_REG("$2");
    u8 stored_value;
    u8 *cursor4;
    u8 *cursor1;
    void *node;
    void *initial_node;
    void *initial_data;

    stage = FIELD(arg0, s32, 0x8C);
    difference = FIELD(arg0, s32, 0x88) - stage;
    scaled = FIELD(arg0, s32, 0x84) * 0x10;
    quotient = (difference * scaled) / FIELD(arg0, s32, 0x80);
    index = 0;
    cursor4 = arg0;
    cursor1 = arg0;
    initial_node = FIELD(arg0, void *, 0x1A4);
    initial_data = FIELD(initial_node, void *, 4);
    quotient += 10;
    FIELD(initial_data, s16, 0xA) = stage * 0x10 + quotient;

loop:
    value = FIELD(cursor1, u8, 0x7C);
    if (index == FIELD(arg0, s32, 0x88)) {
        s32 tail_numerator;
        register s32 tail_value ASM_REG("$5");
        register s32 tail_quotient ASM_REG("$3");

        tail_value = value;
        tail_numerator = 8;
        result = FIELD(arg0, s32, 0x80);
        current = FIELD(arg0, s32, 0x84);
        tail_numerator -= tail_value;
        result -= current;
        result++;
        tail_quotient = tail_numerator / result;
        ASM_KEEP(tail_quotient);
        func_800232F4(current, tail_value, cursor4, cursor1);
        result = tail_value + tail_quotient;
        return result;
    }

    slot = cursor1 + 0x7C;
    ASM_KEEP_NV(slot);
    value2 = value;
    if (value2 != 0) {
        ASM_KEEP_NV(value2);
        value2--;
    }
    *slot = value2;
    stored_value = FIELD(cursor1, u8, 0x7C);

    FIELD(FIELD(FIELD(cursor4, void *, 0x1C8), void *, 4), s16, 8) =
        stored_value + 0x24;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1D8), void *, 4), s16, 8) =
        stored_value + 0x8F;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1A8), void *, 4), s16, 8) =
        stored_value + 9;
    index++;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1B8), void *, 4), s16, 8) =
        stored_value + 0x42;

    FIELD(FIELD(FIELD(cursor4, void *, 0x1C8), void *, 4), u8, 0) =
        FIELD(cursor1, u8, 0x7C) * 3 + 0x68;
    FIELD(FIELD(FIELD(cursor4, void *, 0x1C8), void *, 4), u8, 1) =
        FIELD(cursor1, u8, 0x7C) * 3 + 0x68;
    node = FIELD(cursor4, void *, 0x1C8);
    cursor4 += 4;
    FIELD(FIELD(node, void *, 4), u8, 2) =
        FIELD(cursor1, u8, 0x7C) * 4 + 0x60;
    cursor1++;
    if (index < 3) {
        goto loop;
    }

    final_current = FIELD(arg0, s32, 0x84);
    if (final_current < FIELD(arg0, s32, 0x80)) {
        result = final_current + 1;
        FIELD(arg0, s32, 0x84) = result;
    } else {
        result = final_current + 1;
    }
    return result;
}
