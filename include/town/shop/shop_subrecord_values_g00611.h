#ifndef TOWN_SHOP_SHOP_SUBRECORD_VALUES_G00611_H
#define TOWN_SHOP_SHOP_SUBRECORD_VALUES_G00611_H
/* Shop subrecord values declarations (G00611). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3FDC. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B173C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B173C_0;

/* arg0 in set_shop_change_indicator_color */
typedef struct S_800B173C_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800B173C_1;

struct S_800B0FD4_0;

/* extern */
typedef struct S_800B1778_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B1778_0;

/* Functions defined in this translation unit. */
void set_shop_change_indicator_color(S_800B173C_0 *record, s32 target_value);
void set_shop_subrecord_values(s32 record_address, s32 value_10, s32 value_08);

#endif
