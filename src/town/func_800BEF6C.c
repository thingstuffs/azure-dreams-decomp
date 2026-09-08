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

/* Advance the two coordinates and propagate status flags to the object and global state. */
void func_800BC6CC(void *object_data, void *motion, void *status) {
    func_800478B8(status);
    ((S_800BC6CC_0 *)motion)->unk_00 = (s32) (((S_800BC6CC_0 *)motion)->unk_00 + ((S_800BC6CC_0 *)motion)->unk_0C);
    ((S_800BC6CC_0 *)motion)->unk_04 = (s32) (((S_800BC6CC_0 *)motion)->unk_04 + ((S_800BC6CC_0 *)motion)->unk_10);
    if (((Rec_D_80082E80 *)status)->unk_14.at00_u16.v & 0x6000) {
        (*(u16 *)((u8 *)object_data + -2)) = (u16) (((S_800BC6CC_2_pre *)object_data)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
