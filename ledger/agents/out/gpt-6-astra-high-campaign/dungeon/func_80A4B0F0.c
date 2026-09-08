#include "common.h"
#include "m2c_compat.h"

typedef struct S_801748F0_0 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} S_801748F0_0;   /* arg0 in func_801748F0; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

/* Decrement the record counter and set completion flags when it reaches zero or becomes negative. */
void func_801748F0(void *record_data) {
    u16 remaining_count;

    remaining_count = ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
