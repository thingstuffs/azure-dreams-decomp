#include "common.h"
#include "m2c_compat.h"

typedef struct S_80814610_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80814610_0;   /* arg1 in func_80814610 */

typedef struct S_80814610_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80814610_1;   /* arg2 in func_80814610 */

typedef struct S_80814610_2_pre {
    u16 unk_00;
} S_80814610_2_pre;   /* the 0x2 bytes before arg0 in func_80814610, addressed as arg0[-1] */


M2C_UNK func_8003EA54();                 /* extern */
extern s32 D_80084D5C;

void func_80814610(void *arg0, void *arg1, void *arg2) {
    s32 temp_a2;
    u8 temp_v0;

    temp_a2 = ((S_80814610_0 *)arg1)->unk_14;
    if (temp_a2 != 0) {
        ((S_80814610_0 *)arg1)->unk_08 = (s32) (((S_80814610_0 *)arg1)->unk_08 + temp_a2);
        ((S_80814610_0 *)arg1)->unk_14 = (s32) (((S_80814610_0 *)arg1)->unk_14 + 0x18000);
        temp_v0 = ((S_80814610_1 *)arg2)->unk_0E - 0x20;
        ((S_80814610_1 *)arg2)->unk_0E = temp_v0;
        ((S_80814610_1 *)arg2)->unk_0D = temp_v0;
        ((S_80814610_1 *)arg2)->unk_0C = temp_v0;
    }
    func_8003EA54(arg2);
    if (((S_80814610_1 *)arg2)->unk_14 & 0x6000) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80814610_2_pre *)arg0)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}

/* MECHANISM: Natural arg lifetimes produce the retail 0x20 frame with s0=arg2 and s1=arg0.
   The one-argument callee shape removes the dead a1 move and closes the displacement cascade.
   The 2.7.2-G0 route preserves the established scalar declaration while emitting retail hi/lo accesses. */
