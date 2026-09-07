#include "common.h"


extern void func_800232F4(s32 current, s32 value, void *cursor4,
                          void *cursor1);


typedef struct S_80023258_0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    u8 pad_90[0x114];
    void * unk_1A4;
} S_80023258_0;   /* arg0 in func_80023258 */

typedef struct S_80023258_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_1;   /* initial_node in func_80023258 */

typedef struct S_80023258_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80023258_2;   /* initial_data in func_80023258 */

typedef struct S_80023258_3 {
    u8 pad_00[0x7C];
    u8 unk_7C;
} S_80023258_3;   /* cursor1 in func_80023258 */

typedef struct S_80023258_4 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_80023258_4;   /* cursor4 in func_80023258 */

typedef struct S_80023258_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_5;   /* node in func_80023258 */

typedef struct S_80023258_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_6;   /* ((S_80023258_4 *)cursor4)->unk_1C8 in func_80023258 */

typedef struct S_80023258_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_7;   /* ((S_80023258_4 *)cursor4)->unk_1D8 in func_80023258 */

typedef struct S_80023258_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_8;   /* ((S_80023258_4 *)cursor4)->unk_1A8 in func_80023258 */

typedef struct S_80023258_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_9;   /* ((S_80023258_4 *)cursor4)->unk_1B8 in func_80023258 */

typedef struct S_80023258_10 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80023258_10;   /* ((S_80023258_5 *)node)->unk_04 in func_80023258 */

typedef struct S_80023258_11 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x6];
    s16 unk_08;
} S_80023258_11;   /* ((S_80023258_6 *)(((S_80023258_4 *)cursor4)->unk_1C8))->unk_04 in func_80023258 */

typedef struct S_80023258_12 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_12;   /* ((S_80023258_7 *)(((S_80023258_4 *)cursor4)->unk_1D8))->unk_04 in func_80023258 */

typedef struct S_80023258_13 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_13;   /* ((S_80023258_8 *)(((S_80023258_4 *)cursor4)->unk_1A8))->unk_04 in func_80023258 */

typedef struct S_80023258_14 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_14;   /* ((S_80023258_9 *)(((S_80023258_4 *)cursor4)->unk_1B8))->unk_04 in func_80023258 */

s32 func_80023258(S_80023258_0 *arg0)
{
    s32 stage;
    s32 difference;
    s32 scaled;
    s32 quotient;
    s32 current;
    s32 final_current;
    s32 index;
    s32 result;
    register u8 *slot ASM_REG("$8");
    s32 value;
    register u8 value2 ASM_REG("$2");
    u8 stored_value;
    u8 *cursor4;
    u8 *cursor1;
    void *node;
    S_80023258_1 *initial_node;
    S_80023258_2 *initial_data;

    stage = arg0->unk_8C;
    difference = arg0->unk_88 - stage;
    scaled = arg0->unk_84 * 0x10;
    quotient = (difference * scaled) / arg0->unk_80;
    index = 0;
    cursor4 = arg0;
    cursor1 = arg0;
    initial_node = arg0->unk_1A4;
    initial_data = initial_node->unk_04;
    quotient += 10;
    initial_data->unk_0A = stage * 0x10 + quotient;

loop:
    value = ((S_80023258_3 *)cursor1)->unk_7C;
    if (index == arg0->unk_88) {
        s32 tail_numerator;
        register s32 tail_value ASM_REG("$5");
        register s32 tail_quotient ASM_REG("$3");

        tail_value = value;
        tail_numerator = 8;
        result = arg0->unk_80;
        current = arg0->unk_84;
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
    stored_value = ((S_80023258_3 *)cursor1)->unk_7C;

    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)cursor4)->unk_1C8))->unk_04))->unk_08 =
        stored_value + 0x24;
    ((S_80023258_12 *)(((S_80023258_7 *)(((S_80023258_4 *)cursor4)->unk_1D8))->unk_04))->unk_08 =
        stored_value + 0x8F;
    ((S_80023258_13 *)(((S_80023258_8 *)(((S_80023258_4 *)cursor4)->unk_1A8))->unk_04))->unk_08 =
        stored_value + 9;
    index++;
    ((S_80023258_14 *)(((S_80023258_9 *)(((S_80023258_4 *)cursor4)->unk_1B8))->unk_04))->unk_08 =
        stored_value + 0x42;

    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)cursor4)->unk_1C8))->unk_04))->unk_00 =
        ((S_80023258_3 *)cursor1)->unk_7C * 3 + 0x68;
    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)cursor4)->unk_1C8))->unk_04))->unk_01 =
        ((S_80023258_3 *)cursor1)->unk_7C * 3 + 0x68;
    node = ((S_80023258_4 *)cursor4)->unk_1C8;
    cursor4 += 4;
    ((S_80023258_10 *)(((S_80023258_5 *)node)->unk_04))->unk_02 =
        ((S_80023258_3 *)cursor1)->unk_7C * 4 + 0x60;
    cursor1++;
    if (index < 3) {
        goto loop;
    }

    final_current = arg0->unk_84;
    if (final_current < arg0->unk_80) {
        result = final_current + 1;
        arg0->unk_84 = result;
    } else {
        result = final_current + 1;
    }
    return result;
}
