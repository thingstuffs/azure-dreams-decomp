#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B5174_1 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
} S_800B5174_1;   /* arg1 in layout_three_display_elements */

typedef struct S_800B5174_2 {
    s32 * unk_00;
    void * unk_04;
} S_800B5174_2;   /* ((S_800B5174_1 *)arg1)->unk_00 in layout_three_display_elements */

typedef struct S_800B5174_3 {
    s32 unk_00;
    void * unk_04;
} S_800B5174_3;   /* ((S_800B5174_1 *)arg1)->unk_04 in layout_three_display_elements */

typedef struct S_800B5174_4 {
    s32 * unk_00;
    void * unk_04;
} S_800B5174_4;   /* ((S_800B5174_1 *)arg1)->unk_08 in layout_three_display_elements */

typedef struct S_800B5174_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_5;   /* ((S_800B5174_2 *)(((S_800B5174_1 *)arg1)->unk_00))->unk_04 in layout_three_display_elements */

typedef struct S_800B5174_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_6;   /* ((S_800B5174_3 *)(((S_800B5174_1 *)arg1)->unk_04))->unk_04 in layout_three_display_elements */

typedef struct S_800B5174_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_7;   /* ((S_800B5174_4 *)(((S_800B5174_1 *)arg1)->unk_08))->unk_04 in layout_three_display_elements */


void *set_complementary_entry_bytes();               /* extern */
extern M2C_UNK D_80077FBC;
extern u8 D_800D1794;

typedef struct S_800B5174_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800B5174_0;   /* arg0 in layout_three_display_elements */

/* Positions three display elements, assigns their content, and updates the shared value buffer. */
void *layout_three_display_elements(S_800B5174_0 *values, S_800B5174_1 *elements, s32 content) {
    ((S_800B5174_5 *)(((S_800B5174_2 *)(elements->unk_00))->unk_04))->unk_08 = -0x38;
    ((S_800B5174_5 *)(((S_800B5174_2 *)(elements->unk_00))->unk_04))->unk_0A = 8;
    ((S_800B5174_2 *)(elements->unk_00))->unk_00 = &D_80077FBC;
    ((S_800B5174_6 *)(((S_800B5174_3 *)(elements->unk_04))->unk_04))->unk_08 = -0x38;
    ((S_800B5174_6 *)(((S_800B5174_3 *)(elements->unk_04))->unk_04))->unk_0A = 8;
    ((S_800B5174_3 *)(elements->unk_04))->unk_00 = content;
    ((S_800B5174_7 *)(((S_800B5174_4 *)(elements->unk_08))->unk_04))->unk_08 = -0x18;
    ((S_800B5174_7 *)(((S_800B5174_4 *)(elements->unk_08))->unk_04))->unk_0A = 0x30;
    ((S_800B5174_4 *)(elements->unk_08))->unk_00 = &D_800D1794;
    set_complementary_entry_bytes(&D_800D1794, values->unk_28);
    set_complementary_entry_bytes(&D_800D1794 + 0xC, values->unk_29);
    return elements;
}
