/* Lay out three display elements and complementary values (G00630). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B79CC. */
#include "town/shop/display_element_layout_g00630.h"
#include "town/shop.h"

/* Set two entry bytes to complementary values derived from the amount. */
void *set_complementary_entry_bytes(void *entry, s16 amount) {
    u8 *base = entry;
    s32 remaining;
    s32 hidden_v1;

    if (amount < 300) {
        s32 quotient = amount / 4;

        hidden_v1 = quotient + 1;
    } else {
        hidden_v1 = 64;
    }

    remaining = 64;
    remaining -= hidden_v1;
    base[2] = remaining;
    {
        void *result = base;

        base[10] = hidden_v1;
        return result;
    }
}

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
