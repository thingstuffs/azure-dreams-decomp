#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800BC6CC_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800BC6CC_0;   /* arg1 in func_800BC6CC */


typedef struct S_800BC6CC_2_pre {
    u16 unk_00;
} S_800BC6CC_2_pre;   /* the 0x2 bytes before arg0 in func_800BC6CC, addressed as arg0[-1] */


extern int func_800478B8();
extern int D_800814A0;

void func_800BC6CC(void *arg0, void *arg1, void *arg2) {
    func_800478B8(arg2);
    ((S_800BC6CC_0 *)arg1)->unk_00 = (s32) (((S_800BC6CC_0 *)arg1)->unk_00 + ((S_800BC6CC_0 *)arg1)->unk_0C);
    ((S_800BC6CC_0 *)arg1)->unk_04 = (s32) (((S_800BC6CC_0 *)arg1)->unk_04 + ((S_800BC6CC_0 *)arg1)->unk_10);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800BC6CC_2_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
