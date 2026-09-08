#include "common.h"

typedef struct S_800DC0BC_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800DC0BC_0;   /* owner in func_800DC0BC */

typedef struct S_800DC0BC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800DC0BC_1;   /* arg0 in func_800DC0BC */

typedef struct S_800DC0BC_2 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_800DC0BC_2;   /* *page in func_800DC0BC */



extern void *D_800814A8;
extern void func_800DC078(s32, u8);

/* Updates two target entries when their cached values differ from the current values. */
void func_800DC0BC(S_800DC0BC_1 *cached_values, s32 *target_base) {
    void **page;
    S_800DC0BC_0 *owner;
    u8 first_value;
    u8 second_value;

    page = &D_800814A8;
    owner = *page;
    first_value = owner->unk_28;
    if (first_value != cached_values->unk_10) {
        func_800DC078(target_base[0], owner->unk_28);
        cached_values->unk_10 = ((S_800DC0BC_2 *)(*page))->unk_28;
    }
    owner = *page;
    second_value = owner->unk_29;
    if (second_value != cached_values->unk_14) {
        func_800DC078(target_base[0] + 0xC, owner->unk_29);
        cached_values->unk_14 = ((S_800DC0BC_2 *)(*page))->unk_29;
    }
}
