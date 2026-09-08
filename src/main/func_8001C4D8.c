#include "common.h"



typedef struct S_804034D8_0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    u8 pad_90[0x12C];
    void * unk_1BC;
} S_804034D8_0;   /* arg0 in func_804034D8 */

typedef struct S_804034D8_1 {
    u8 pad_00[0x7C];
    u8 unk_7C;
} S_804034D8_1;   /* cursor1 in func_804034D8 */

typedef struct S_804034D8_2 {
    u8 pad_00[0x1C0];
    void * unk_1C0;
    u8 pad_1C4[0xC];
    void * unk_1D0;
    u8 pad_1D4[0xC];
    void * unk_1E0;
    u8 pad_1E4[0xC];
    void * unk_1F0;
} S_804034D8_2;   /* cursor4 in func_804034D8 */

typedef struct S_804034D8_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_3;   /* node in func_804034D8 */

typedef struct S_804034D8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_4;   /* ((S_804034D8_0 *)arg0)->unk_1BC in func_804034D8 */

typedef struct S_804034D8_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_5;   /* ((S_804034D8_2 *)cursor4)->unk_1E0 in func_804034D8 */

typedef struct S_804034D8_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_6;   /* ((S_804034D8_2 *)cursor4)->unk_1F0 in func_804034D8 */

typedef struct S_804034D8_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_7;   /* ((S_804034D8_2 *)cursor4)->unk_1C0 in func_804034D8 */

typedef struct S_804034D8_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_804034D8_8;   /* ((S_804034D8_2 *)cursor4)->unk_1D0 in func_804034D8 */

typedef struct S_804034D8_9 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_804034D8_9;   /* ((S_804034D8_3 *)node)->unk_04 in func_804034D8 */

typedef struct S_804034D8_10 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_804034D8_10;   /* ((S_804034D8_4 *)(((S_804034D8_0 *)arg0)->unk_1BC))->unk_04 in func_804034D8 */

typedef struct S_804034D8_11 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x6];
    s16 unk_08;
} S_804034D8_11;   /* ((S_804034D8_5 *)(((S_804034D8_2 *)cursor4)->unk_1E0))->unk_04 in func_804034D8 */

typedef struct S_804034D8_12 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_804034D8_12;   /* ((S_804034D8_6 *)(((S_804034D8_2 *)cursor4)->unk_1F0))->unk_04 in func_804034D8 */

typedef struct S_804034D8_13 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_804034D8_13;   /* ((S_804034D8_7 *)(((S_804034D8_2 *)cursor4)->unk_1C0))->unk_04 in func_804034D8 */

typedef struct S_804034D8_14 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_804034D8_14;   /* ((S_804034D8_8 *)(((S_804034D8_2 *)cursor4)->unk_1D0))->unk_04 in func_804034D8 */

void func_804034D8(S_804034D8_0 *arg0)
{
    s32 stage;
    s32 difference;
    s32 scaled;
    s32 product;
    s32 quotient;
    s32 final_current;
    u8 *slot;
    register s32 index ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 value;
    u32 next_value;
    u8 stored_value;
    void *cursor4;
    void *cursor1;
    S_804034D8_3 *node;

    stage = arg0->unk_8C;
    difference = arg0->unk_88 - stage;
    scaled = arg0->unk_84 * 0x10;
    product = difference * scaled;
    quotient = product / arg0->unk_80;
    index = 0;
    cursor4 = arg0;
    cursor1 = arg0;
    quotient += 10;
    ((S_804034D8_10 *)(((S_804034D8_4 *)(arg0->unk_1BC))->unk_04))->unk_0A =
        stage * 0x10 + quotient;

loop:
    slot = (u8 *)cursor1 + 0x7C;
    value = *slot;
    if (index == arg0->unk_88) {
        s32 tail_numerator;
        s32 tail_denominator;

        tail_numerator = 8;
        tail_denominator = arg0->unk_80;
        tail_numerator -= value;
        tail_denominator -= arg0->unk_84;
        tail_denominator++;
        quotient = tail_numerator / tail_denominator;
        next_value = value + quotient;
    } else {
        next_value = value;
        if (next_value != 0)
            next_value--;
    }
    *slot = next_value;
    stored_value = ((S_804034D8_1 *)cursor1)->unk_7C;

    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)cursor4)->unk_1E0))->unk_04))->unk_08 =
        stored_value + 0x24;
    ((S_804034D8_12 *)(((S_804034D8_6 *)(((S_804034D8_2 *)cursor4)->unk_1F0))->unk_04))->unk_08 =
        stored_value + 0x8F;
    ((S_804034D8_13 *)(((S_804034D8_7 *)(((S_804034D8_2 *)cursor4)->unk_1C0))->unk_04))->unk_08 =
        stored_value + 9;
    index++;
    ((S_804034D8_14 *)(((S_804034D8_8 *)(((S_804034D8_2 *)cursor4)->unk_1D0))->unk_04))->unk_08 =
        stored_value + 0x42;

    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)cursor4)->unk_1E0))->unk_04))->unk_00 =
        ((S_804034D8_1 *)cursor1)->unk_7C * 3 + 0x68;
    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)cursor4)->unk_1E0))->unk_04))->unk_01 =
        ((S_804034D8_1 *)cursor1)->unk_7C * 3 + 0x68;
    node = ((S_804034D8_2 *)cursor4)->unk_1E0;
    cursor4 += 4;
    ((S_804034D8_9 *)(node->unk_04))->unk_02 =
        ((S_804034D8_1 *)cursor1)->unk_7C * 4 + 0x60;
    cursor1++;
    if (index < 4)
        goto loop;

    final_current = arg0->unk_84;
    if (final_current < arg0->unk_80)
        arg0->unk_84 = final_current + 1;
}
