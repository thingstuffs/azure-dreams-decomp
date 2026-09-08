#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800374F4();                     /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_8009539C();                      /* extern */
extern M2C_UNK D_800A38A8;
extern M2C_UNK D_800D0B20;


typedef struct S_800A378C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x1E];
    s16 unk_22;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_800A378C_0;   /* arg0 in func_800A378C */



void func_800A378C(S_800A378C_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2) {
    s32 temp_v0;

    temp_v0 = arg0->unk_24 - 1;
    arg0->unk_24 = temp_v0;
    if (temp_v0 < 0) {
        arg1->unk_0C.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_14.as_s32 = 0;
        arg2->unk_0C.at02_s8.v = 0x40;
        arg2->unk_0C.at01_s8.v = 0x40;
        arg2->unk_0C.at00_s8.v = 0x40;
        arg2->unk_10.as_s16 = 0x20;
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x1C);
        arg0->unk_00 = &D_800A38A8;
        arg1->unk_0C.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_14.as_s32 =
            ((((u16) func_800374F4(0x1000)) << 1) + 0x2000) << 4;
        return;
    }
    arg1->unk_0C.as_s32 = (s32) (arg1->unk_0C.as_s32 - arg0->unk_2C);
    arg1->unk_10.at00_s32.v = (s32) (arg1->unk_10.at00_s32.v - arg0->unk_30);
    arg1->unk_14.as_s32 = (s32) (arg1->unk_14.as_s32 - arg0->unk_34);
    func_8009539C(arg1);
    if (*(&D_800D0B20 + arg0->unk_22) != 0) {
        func_800478B8(arg2);
    }
}
/* MECHANISM: Restoring the post-call u16 transform keeps arg1 live across the call,
   naturally producing the retail s1/s0/s2 hold set and seven omitted words.
   Single-element M2C_UNK table indexing fixes the remaining sll 4 to retail sll 2. */
