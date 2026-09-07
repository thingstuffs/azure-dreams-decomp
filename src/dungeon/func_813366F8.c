#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_800A4ACC();                      /* extern */



void func_8016D6F8(Rec_func_800A9E70_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, Rec_D_800E3D7C *arg3) {
    arg3->unk_71.as_u8 = (u8) (arg3->unk_71.as_u8 & 0x7F);
    arg0->unk_8C = 0;
    arg0->unk_9A.as_s8 = 0x17;
    arg0->unk_9B.as_s8 = 0;
    func_800A4ACC(arg3);
    arg3->unk_6D.as_u8 = (u8) (arg3->unk_6D.as_u8 - 1);
}
