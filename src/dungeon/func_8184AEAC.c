#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800DEB28;

typedef struct S_800246AC_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
} S_800246AC_0;   /* arg0 in func_800246AC */

typedef struct S_800246AC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800246AC_1;   /* arg2 in func_800246AC */

typedef struct S_800246AC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800246AC_2;   /* arg1 in func_800246AC */

void func_800246AC(S_800246AC_0 *arg0, S_800246AC_2 *arg1, S_800246AC_1 *arg2) {
    s16 temp_a0;
    s32 temp_v1;
    s32 var_v0;

    temp_a0 = arg0->unk_08;
    temp_v1 = temp_a0 + 0x40;
    var_v0 = temp_v1;
    if (temp_v1 < 0) {
        var_v0 = temp_a0 + 0x103F;
    }
    arg0->unk_08 = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        func_8003DB94(arg2, &D_800DEB28, 0);
        arg1->unk_02 = (s16) (arg0->unk_00 + ((s32) ((func_800644B8(arg0->unk_08) >> 4) * 0x1C) >> 8));
        arg1->unk_06 = (s16) (arg0->unk_02 + ((s32) ((func_80064584(arg0->unk_08) >> 4) * 0x1C) >> 8));
    }
}
