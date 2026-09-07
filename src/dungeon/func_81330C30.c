#include "common.h"
#include "m2c_compat.h"

typedef struct S_80167C30_0 {
    u16 unk_00;
    u8 pad_02[0x18];
    u16 unk_1A;
} S_80167C30_0;   /* arg0 in func_80167C30; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

void func_80167C30(void *arg0) {
    u16 temp_v0;

    temp_v0 = ((S_80167C30_0 *)((u8 *)arg0 - 0x2))->unk_1A - 1;
    ((S_80167C30_0 *)((u8 *)arg0 - 0x2))->unk_1A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_80167C30_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_80167C30_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
