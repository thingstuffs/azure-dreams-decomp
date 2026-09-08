#include "common.h"

typedef struct S_80026D0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80026D0C_0;   /* arg0 in func_80026D0C */

typedef struct S_80026D0C_1 {
    void * unk_00;
    void * unk_04;
    s16 unk_08;
} S_80026D0C_1;   /* temp_a1 in func_80026D0C */

typedef struct S_80026D0C_2 {
    void * unk_00;
    void * unk_04;
} S_80026D0C_2;   /* temp_v1_2 in func_80026D0C */

typedef struct S_80026D0C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026D0C_3;   /* ((S_80026D0C_0 *)arg0)->unk_0C in func_80026D0C */

typedef struct S_80026D0C_4 {
    u8 pad_00[0xA];
    u8 unk_0A;
} S_80026D0C_4;   /* ((S_80026D0C_1 *)temp_a1)->unk_00 in func_80026D0C */

typedef struct S_80026D0C_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80026D0C_5;   /* ((S_80026D0C_2 *)temp_v1_2)->unk_04 in func_80026D0C */

typedef struct S_80026D0C_6 {
    u8 pad_00[0xB];
    u8 unk_0B;
} S_80026D0C_6;   /* ((S_80026D0C_2 *)temp_v1_2)->unk_00 in func_80026D0C */

typedef struct S_80026D0C_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026D0C_7;   /* ((S_80026D0C_3 *)(((S_80026D0C_0 *)arg0)->unk_0C))->unk_04 in func_80026D0C */



/* Position paired display elements in a repeating nine-column grid. */
void func_80026D0C(S_80026D0C_0 *display, s32 cell_index) {
    s32 row_y;
    s32 x_offset;
    s32 column_x;
    S_80026D0C_1 *element_node;
    S_80026D0C_2 *element;

    column_x = ((cell_index % 72) % 9) * 0xB;
    ((S_80026D0C_7 *)(((S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_08 =
        (s16)(column_x - 0x2B);
    row_y = ((cell_index % 72) / 9) * 0x10;
    ((S_80026D0C_7 *)(((S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_0A =
        (s16)(row_y + 0xF);
    element_node = display->unk_10;
    x_offset = ((S_80026D0C_4 *)(element_node->unk_00))->unk_0A;
    element_node = element_node->unk_04;
    x_offset = (u32)x_offset >> 1;
    x_offset -= 0x29;
    element_node->unk_08 = (s16)(column_x + x_offset);
    element = display->unk_10;
    ((S_80026D0C_5 *)(element->unk_04))->unk_0A =
        (s16)(row_y + ((((S_80026D0C_6 *)(element->unk_00))->unk_0B >> 1) + 0xF));
}
