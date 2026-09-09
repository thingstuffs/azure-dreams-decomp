#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B3178_3 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800B3178_3;   /* *var_s0 in func_800B3178 */

typedef struct S_800B3178_4 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
} S_800B3178_4;   /* ((S_800B3178_3 *)(*var_s0))->unk_04 in func_800B3178 */




s32 func_8004AC3C();                   /* extern */
s32 func_8004DC14();                        /* extern */

typedef struct S_800B3178_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B3178_0;   /* arg1 in func_800B3178 */

typedef struct S_800B3178_1 {
    s32 unk_00;
    s8 * unk_04;
} S_800B3178_1;   /* *var_s0 in func_800B3178 */

typedef struct S_800B3178_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B3178_2;   /* *var_s1 in func_800B3178 */

/* Populate up to ten page entries and set their type-dependent brightness. */
void func_800B3178(void **entries, S_800B3178_0 *page_info, s32 source_table) {
    s32 lookup_param;
    s32 page_index;
    s32 source_index;
    s32 entry_count;
    s32 normal_shade;
    s32 dim_shade;
    void **entry;
    void **source;

    entry_count = 0;
    dim_shade = 0x40;
    normal_shade = 0x80;
    page_index = page_info->unk_00;
    entry = entries;
    source_index = page_index * 0xA;
    source = (page_index * 0x28) + source_table;
next_entry:
    if (source_index < page_info->unk_0C) {
        ((S_800B3178_1 *)(*entry))->unk_00 = func_8004DC14(func_8004AC3C(*source, &lookup_param), lookup_param);
        if (((S_800B3178_2 *)(*source))->unk_01 == 0x13) {
            *((S_800B3178_1 *)(*entry))->unk_04 = dim_shade;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*entry))->unk_04))->unk_01 = dim_shade;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*entry))->unk_04))->unk_02 = dim_shade;
        } else {
            *((S_800B3178_1 *)(*entry))->unk_04 = normal_shade;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*entry))->unk_04))->unk_01 = normal_shade;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*entry))->unk_04))->unk_02 = normal_shade;
        }
        entry += 1;
        entry_count += 1;
        source += 1;
        source_index += 1;
        if (entry_count < 0xA) {
            goto next_entry;
        }
    }
}
