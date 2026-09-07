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

void func_800DC0BC(S_800DC0BC_1 *arg0, s32 *arg1) {
    void **page;
    S_800DC0BC_0 *owner;
    u8 temp_v1;
    u8 temp_v1_2;

    page = &D_800814A8;
    owner = *page;
    temp_v1 = owner->unk_28;
    if (temp_v1 != arg0->unk_10) {
        func_800DC078(arg1[0], owner->unk_28);
        arg0->unk_10 = ((S_800DC0BC_2 *)(*page))->unk_28;
    }
    owner = *page;
    temp_v1_2 = owner->unk_29;
    if (temp_v1_2 != arg0->unk_14) {
        func_800DC078(arg1[0] + 0xC, owner->unk_29);
        arg0->unk_14 = ((S_800DC0BC_2 *)(*page))->unk_29;
    }
}
