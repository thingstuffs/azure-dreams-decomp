#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800374F4();                     /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800A388C();                            /* extern */
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

typedef struct S_800A378C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A378C_1;   /* arg1 in func_800A378C */

typedef struct S_800A378C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_800A378C_2;   /* arg2 in func_800A378C */

void func_800A378C(S_800A378C_0 *arg0, S_800A378C_1 *arg1, S_800A378C_2 *arg2) {
    s32 temp_v0;

    temp_v0 = arg0->unk_24 - 1;
    arg0->unk_24 = temp_v0;
    if (temp_v0 < 0) {
        arg1->unk_0C = 0;
        arg1->unk_10 = 0;
        arg1->unk_14 = 0;
        arg2->unk_0E = 0x40;
        arg2->unk_0D = 0x40;
        arg2->unk_0C = 0x40;
        arg2->unk_10 = 0x20;
        arg2->unk_14 = (u16) (arg2->unk_14 | 0x1C);
        arg0->unk_00 = &D_800A38A8;
        arg1->unk_0C = 0;
        arg1->unk_10 = 0;
        arg1->unk_14 =
            ((((u16) func_800374F4(0x1000)) << 1) + 0x2000) << 4;
        func_800A388C();
        return;
    }
    arg1->unk_0C = (s32) (arg1->unk_0C - arg0->unk_2C);
    arg1->unk_10 = (s32) (arg1->unk_10 - arg0->unk_30);
    arg1->unk_14 = (s32) (arg1->unk_14 - arg0->unk_34);
    func_8009539C(arg1);
    if (*(&D_800D0B20 + arg0->unk_22) != 0) {
        func_800478B8(arg2);
    }
}
/* MECHANISM: Restoring the post-call u16 transform keeps arg1 live across the call,
   naturally producing the retail s1/s0/s2 hold set and seven omitted words.
   Single-element M2C_UNK table indexing fixes the remaining sll 4 to retail sll 2. */
