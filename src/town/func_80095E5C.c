#include "common.h"

typedef struct S_800935BC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800935BC_0;   /* arg1 in func_800935BC */

typedef struct S_800935BC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x24];
    s16 unk_30;
    s16 unk_32;
} S_800935BC_1;   /* arg0 in func_800935BC */



extern void func_80093D48(void);

void func_800935BC(S_800935BC_1 *arg0, S_800935BC_0 *arg1) {
    s16 temp_v0;

    arg1->unk_00 = (s32) (((s32) (arg0->unk_30 << 0x10) + arg1->unk_00) / 2);
    arg1->unk_04 = (s32) (((s32) (arg0->unk_32 << 0x10) + arg1->unk_04) / 2);
    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if (temp_v0 < 0) {
        func_80093D48();
    }
}
