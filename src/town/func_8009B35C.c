#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                      /* extern */
extern M2C_UNK D_80097EFC;
extern M2C_UNK D_800D0170;



void func_80098ABC(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1) {
    func_80094984(&D_800D0170, arg0);
    arg0->unk_04.as_pm = &D_80097EFC;
    func_80099754(arg1);
    arg1->unk_0C.as_s32 = 0xFFFE0000;
    arg1->unk_10.at00_s32.v = 0x40000;
    arg1->unk_14.as_s32 = 0xFFF90000;
    arg0->unk_10.as_s16 = 0xE00;
}
