#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C8C8_1 {
    u8 pad_00[0x1B8];
    void * unk_1B8;
} S_8001C8C8_1;   /* arg0 in func_8001C8C8 */

typedef struct S_8001C8C8_2 {
    u8 pad_00[0x1C0];
    void * unk_1C0;
    u8 pad_1C4[0xC];
    void * unk_1D0;
    u8 pad_1D4[0xC];
    void * unk_1E0;
    u8 pad_1E4[0xC];
    void * unk_1F0;
} S_8001C8C8_2;   /* var_a0 in func_8001C8C8 */

typedef struct S_8001C8C8_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_3;   /* ((S_8001C8C8_1 *)arg0)->unk_1B8 in func_8001C8C8 */

typedef struct S_8001C8C8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_4;   /* ((S_8001C8C8_2 *)var_a0)->unk_1F0 in func_8001C8C8 */

typedef struct S_8001C8C8_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_5;   /* ((S_8001C8C8_2 *)var_a0)->unk_1C0 in func_8001C8C8 */

typedef struct S_8001C8C8_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_6;   /* ((S_8001C8C8_2 *)var_a0)->unk_1D0 in func_8001C8C8 */

typedef struct S_8001C8C8_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_7;   /* ((S_8001C8C8_2 *)var_a0)->unk_1E0 in func_8001C8C8 */

typedef struct S_8001C8C8_8 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001C8C8_8;   /* ((S_8001C8C8_3 *)(((S_8001C8C8_1 *)arg0)->unk_1B8))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_9;   /* ((S_8001C8C8_4 *)(((S_8001C8C8_2 *)var_a0)->unk_1F0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_10;   /* ((S_8001C8C8_5 *)(((S_8001C8C8_2 *)var_a0)->unk_1C0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_11;   /* ((S_8001C8C8_6 *)(((S_8001C8C8_2 *)var_a0)->unk_1D0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_12;   /* ((S_8001C8C8_7 *)(((S_8001C8C8_2 *)var_a0)->unk_1E0))->unk_04 in func_8001C8C8 */




M2C_UNK func_80403698();                      /* extern */
M2C_UNK func_80403738();       /* extern */
M2C_UNK func_804037F4(void *);                            /* extern */
M2C_UNK func_80403868();    /* extern */

typedef struct S_8001C8C8_0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
} S_8001C8C8_0;   /* arg0 in func_8001C8C8 */

/* Initialize the panel and position four rows of display elements. */
void func_8001C8C8(void *panel) {
    s32 lower_x;
    s32 left_x;
    s32 right_x;
    s32 middle_x;
    s32 row_y;
    s32 lower_y;
    s32 row;
    void *row_cursor;

    ((S_8001C8C8_0 *)panel)->unk_80 = 1;
    ((S_8001C8C8_0 *)panel)->unk_84 = 1;
    func_804037F4(panel);
    func_80403868(panel + 4, 0x36, 0x10);
    func_80403698(panel);
    row = 0;
    lower_x = 0x8E;
    left_x = 9;
    right_x = 0x42;
    middle_x = 0x24;
    row_y = 0xA;
    lower_y = 0x82;
    row_cursor = panel;
    ((S_8001C8C8_8 *)(((S_8001C8C8_3 *)(((S_8001C8C8_1 *)panel)->unk_1B8))->unk_04))->unk_0A = 0x22;
    do {
        ((S_8001C8C8_9 *)(((S_8001C8C8_4 *)(((S_8001C8C8_2 *)row_cursor)->unk_1F0))->unk_04))->unk_08 = lower_x;
        ((S_8001C8C8_9 *)(((S_8001C8C8_4 *)(((S_8001C8C8_2 *)row_cursor)->unk_1F0))->unk_04))->unk_0A = lower_y;
        ((S_8001C8C8_10 *)(((S_8001C8C8_5 *)(((S_8001C8C8_2 *)row_cursor)->unk_1C0))->unk_04))->unk_08 = left_x;
        ((S_8001C8C8_10 *)(((S_8001C8C8_5 *)(((S_8001C8C8_2 *)row_cursor)->unk_1C0))->unk_04))->unk_0A = row_y;
        ((S_8001C8C8_11 *)(((S_8001C8C8_6 *)(((S_8001C8C8_2 *)row_cursor)->unk_1D0))->unk_04))->unk_08 = right_x;
        ((S_8001C8C8_11 *)(((S_8001C8C8_6 *)(((S_8001C8C8_2 *)row_cursor)->unk_1D0))->unk_04))->unk_0A = row_y;
        row += 1;
        ((S_8001C8C8_12 *)(((S_8001C8C8_7 *)(((S_8001C8C8_2 *)row_cursor)->unk_1E0))->unk_04))->unk_08 = middle_x;
        lower_y += 0x10;
        ((S_8001C8C8_12 *)(((S_8001C8C8_7 *)(((S_8001C8C8_2 *)row_cursor)->unk_1E0))->unk_04))->unk_0A = row_y;
        row_cursor += 4;
        row_y += 0x10;
    } while (row < 4);
    func_80403738(panel, row_y, lower_y, row);
}
