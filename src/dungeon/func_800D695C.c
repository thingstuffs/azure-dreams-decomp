#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_800DC0BC_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800DC0BC_0;   /* owner in update_cached_target_entries */

typedef struct S_800DC0BC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800DC0BC_1;   /* arg0 in update_cached_target_entries */

typedef struct S_800DC0BC_2 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800DC0BC_2;   /* *page in update_cached_target_entries */


extern void set_scaled_value_and_complement(s32, u8);

/* Updates two target entries when their cached values differ from the current values. */
void update_cached_target_entries(S_800DC0BC_1 *cached_values, s32 *target_base) {
    void **page;
    S_800DC0BC_0 *owner;
    u8 first_value;
    u8 second_value;

    page = &D_800814A8;
    owner = *page;
    first_value = owner->unk_28;
    if (first_value != cached_values->unk_10) {
        set_scaled_value_and_complement(target_base[0], owner->unk_28);
        cached_values->unk_10 = ((S_800DC0BC_2 *)(*page))->unk_28;
    }
    owner = *page;
    second_value = owner->unk_29;
    if (second_value != cached_values->unk_14) {
        set_scaled_value_and_complement(target_base[0] + 0xC, owner->unk_29);
        cached_values->unk_14 = ((S_800DC0BC_2 *)(*page))->unk_29;
    }
}
