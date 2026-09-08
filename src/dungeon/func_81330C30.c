#include "common.h"
#include "m2c_compat.h"

typedef struct S_80167C30_0 {
    u16 unk_00;
    u8 pad_02[0x18];
    u16 unk_1A;
} S_80167C30_0;   /* arg0 in func_80167C30; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

/* Decrement the record count and set record and global flags when it reaches zero. */
void func_80167C30(void *record_data) {
    u16 remaining_count;

    remaining_count = ((S_80167C30_0 *)((u8 *)record_data - 0x2))->unk_1A - 1;
    ((S_80167C30_0 *)((u8 *)record_data - 0x2))->unk_1A = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((S_80167C30_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80167C30_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
