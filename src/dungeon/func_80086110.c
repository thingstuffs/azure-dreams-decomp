#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

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






void func_8008B870(Rec_func_8008ACDC_arg0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    s16 temp_v1;
    M2C_UNK *temp_s4 = D_80083160;

    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    temp_v1 = arg3->unk_64.as_s16;
    if ((temp_v1 < 0) || (arg0->unk_10C & 1)) {
        arg2->unk_14.at00_u16.v = (u16)(arg2->unk_14.at00_u16.v & 0xF7FF);
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008B9D8();
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if (!(D_80013714[0] & 1) && !(D_80083462[0] & 4) && (temp_s4[2] & 0x80)) {
        arg3->unk_8A.as_s16 = 2;
        D_800E4940[0] = 2;
        func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
        D_80082EB0[0] = 0;
        arg0->unk_C8 = 0;
        arg0->unk_104 = 0;
        func_8008B9D8();
        return;
    }
    if ((arg0->unk_9A.as_u8 != 0xD) && (arg3->unk_1C.as_s32 & 0x200)) {
        arg2->unk_14.at00_u16.v = (u16)(arg2->unk_14.at00_u16.v & 0xF7FF);
        func_80090200(arg0, arg1, arg2, arg3);
    }
}
