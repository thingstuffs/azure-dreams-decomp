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

/* Animate the menu selection marker and each row's horizontal offset and color. */
void func_804034D8(S_804034D8_0 *menu)
{
    s32 start_row;
    s32 row_delta;
    s32 scaled_frame;
    s32 move_numerator;
    s32 step;
    s32 frame;
    u8 *offset_slot;
    s32 row_index;
    u32 offset;
    u32 next_offset;
    u8 row_offset;
    void *primitive_cursor;
    void *offset_cursor;
    S_804034D8_3 *color_node;

    start_row = menu->unk_8C;
    row_delta = menu->unk_88 - start_row;
    scaled_frame = menu->unk_84 * 0x10;
    move_numerator = row_delta * scaled_frame;
    step = move_numerator / menu->unk_80;
    row_index = 0;
    primitive_cursor = menu;
    offset_cursor = menu;
    step += 10;
    ((S_804034D8_10 *)(((S_804034D8_4 *)(menu->unk_1BC))->unk_04))->unk_0A =
        start_row * 0x10 + step;

loop:
    offset_slot = (u8 *)offset_cursor + 0x7C;
    offset = *offset_slot;
    if (row_index == menu->unk_88) {
        s32 offset_delta;
        s32 frames_left;

        offset_delta = 8;
        frames_left = menu->unk_80;
        offset_delta -= offset;
        frames_left -= menu->unk_84;
        frames_left++;
        step = offset_delta / frames_left;
        next_offset = offset + step;
    } else {
        next_offset = offset;
        if (next_offset != 0)
            next_offset--;
    }
    do {
        *offset_slot = next_offset;
    } while (0);
    row_offset = ((S_804034D8_1 *)offset_cursor)->unk_7C;

    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)primitive_cursor)->unk_1E0))->unk_04))->unk_08 =
        row_offset + 0x24;
    ((S_804034D8_12 *)(((S_804034D8_6 *)(((S_804034D8_2 *)primitive_cursor)->unk_1F0))->unk_04))->unk_08 =
        row_offset + 0x8F;
    ((S_804034D8_13 *)(((S_804034D8_7 *)(((S_804034D8_2 *)primitive_cursor)->unk_1C0))->unk_04))->unk_08 =
        row_offset + 9;
    row_index++;
    ((S_804034D8_14 *)(((S_804034D8_8 *)(((S_804034D8_2 *)primitive_cursor)->unk_1D0))->unk_04))->unk_08 =
        row_offset + 0x42;

    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)primitive_cursor)->unk_1E0))->unk_04))->unk_00 =
        ((S_804034D8_1 *)offset_cursor)->unk_7C * 3 + 0x68;
    ((S_804034D8_11 *)(((S_804034D8_5 *)(((S_804034D8_2 *)primitive_cursor)->unk_1E0))->unk_04))->unk_01 =
        ((S_804034D8_1 *)offset_cursor)->unk_7C * 3 + 0x68;
    color_node = ((S_804034D8_2 *)primitive_cursor)->unk_1E0;
    primitive_cursor += 4;
    ((S_804034D8_9 *)(color_node->unk_04))->unk_02 =
        ((S_804034D8_1 *)offset_cursor)->unk_7C * 4 + 0x60;
    offset_cursor++;
    if (row_index < 4)
        goto loop;

    frame = menu->unk_84;
    if (frame < menu->unk_80)
        menu->unk_84 = frame + 1;
}
