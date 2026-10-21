#ifndef TOWN_SHOP_DISPLAY_ELEMENT_LAYOUT_G00630_H
#define TOWN_SHOP_DISPLAY_ELEMENT_LAYOUT_G00630_H
/* Lay out three display elements and complementary values (G00630): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B79CC. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B5174_1 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
} S_800B5174_1;

/* arg1 in layout_three_display_elements */
typedef struct S_800B5174_2 {
    s32 * unk_00;
    void * unk_04;
} S_800B5174_2;

/* ((S_800B5174_1 *)arg1)->unk_00 in layout_three_display_elements */
typedef struct S_800B5174_3 {
    s32 unk_00;
    void * unk_04;
} S_800B5174_3;

/* ((S_800B5174_1 *)arg1)->unk_04 in layout_three_display_elements */
typedef struct S_800B5174_4 {
    s32 * unk_00;
    void * unk_04;
} S_800B5174_4;

/* ((S_800B5174_1 *)arg1)->unk_08 in layout_three_display_elements */
typedef struct S_800B5174_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_5;

/* ((S_800B5174_2 *)(((S_800B5174_1 *)arg1)->unk_00))->unk_04 in layout_three_display_elements */
typedef struct S_800B5174_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_6;

/* ((S_800B5174_3 *)(((S_800B5174_1 *)arg1)->unk_04))->unk_04 in layout_three_display_elements */
typedef struct S_800B5174_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B5174_7;

typedef struct S_800B5174_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800B5174_0;

/* extern */
extern M2C_UNK D_80077FBC;
extern u8 D_800D1794;

/* Functions defined in this translation unit. */
void *set_complementary_entry_bytes(void *entry, s16 amount);
void *layout_three_display_elements(S_800B5174_0 *values, S_800B5174_1 *elements, s32 content);

#endif
