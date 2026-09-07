#include "common.h"
#include "m2c_compat.h"

typedef struct S_801748F0_0 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} S_801748F0_0;   /* arg0 in func_801748F0; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

void func_801748F0(void *arg0) {
    u16 temp_v0;

    temp_v0 = ((S_801748F0_0 *)((u8 *)arg0 - 0x2))->unk_1C - 1;
    ((S_801748F0_0 *)((u8 *)arg0 - 0x2))->unk_1C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_801748F0_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_801748F0_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
