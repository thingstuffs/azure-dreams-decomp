#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
extern u16 D_80083462;



void func_801754F0(Rec_func_800A9E70_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, Rec_D_800E3D7C *arg3) {
    arg3->unk_71.as_u8 = (u8) (arg3->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        arg0->unk_8C = 0;
        arg0->unk_9A.as_s8 = 0x17;
        arg0->unk_9B.as_s8 = 0;
        arg0->unk_96.as_s16 = 0;
        func_800A4ACC(arg3);
        arg3->unk_6D.as_u8 = (u8) (arg3->unk_6D.as_u8 - 1);
    }
}
