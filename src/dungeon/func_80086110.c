#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008B9D8();
M2C_UNK func_8008CAA0();
M2C_UNK func_8008CBA0();
M2C_UNK func_8008CF6C();
M2C_UNK func_80090200();
M2C_UNK func_800A2B04();
extern u16 D_80013714[];
extern M2C_UNK D_8004F5F4;
extern s32 D_80082EB0[];
extern M2C_UNK D_80083160[];
extern u16 D_80083462[];
extern s32 D_800E4940[];


typedef struct S_8008B870_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8008B870_0;   /* arg1 in func_8008B870 */

typedef struct S_8008B870_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008B870_1;   /* arg2 in func_8008B870 */

typedef struct S_8008B870_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x44];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008B870_2;   /* arg3 in func_8008B870 */

typedef struct S_8008B870_3 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x2D];
    s32 unk_C8;
    u8 pad_CC[0x38];
    s32 unk_104;
    u8 pad_108[0x4];
    u16 unk_10C;
} S_8008B870_3;   /* arg0 in func_8008B870 */

void func_8008B870(S_8008B870_3 *arg0, S_8008B870_0 *arg1, S_8008B870_1 *arg2, S_8008B870_2 *arg3) {
    s16 temp_v1;
    M2C_UNK *temp_s4 = D_80083160;

    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    temp_v1 = arg3->unk_64;
    if ((temp_v1 < 0) || (arg0->unk_10C & 1)) {
        arg2->unk_14 = (u16)(arg2->unk_14 & 0xF7FF);
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008B9D8();
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if (!(D_80013714[0] & 1) && !(D_80083462[0] & 4) && (temp_s4[2] & 0x80)) {
        arg3->unk_8A = 2;
        D_800E4940[0] = 2;
        func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
        D_80082EB0[0] = 0;
        arg0->unk_C8 = 0;
        arg0->unk_104 = 0;
        func_8008B9D8();
        return;
    }
    if ((arg0->unk_9A != 0xD) && (arg3->unk_1C & 0x200)) {
        arg2->unk_14 = (u16)(arg2->unk_14 & 0xF7FF);
        func_80090200(arg0, arg1, arg2, arg3);
    }
}
