#ifndef TOWN_SHOP_PAGED_SELECTION_REFRESH_G00598_H
#define TOWN_SHOP_PAGED_SELECTION_REFRESH_G00598_H
/* Paged selection refresh declarations (G00598). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B03D0, CL:town/func_800B085C. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800ADFBC_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800ADFBC_0;

typedef struct {
    s32 field_00;
    s32 field_04;
    s32 field_08;
    s32 field_0C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
} TownRecord;

/* Functions defined in this translation unit. */
s32 count_entries_until_second_byte_zero(void *entries);
void refresh_paged_selection_state(TownRecord *record);

#endif
