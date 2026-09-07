#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;



void func_80172548(Rec_func_800A9E70_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            arg0->unk_8C = 0;
            arg0->unk_9A.as_s8 = 0x11;
            arg0->unk_9B.as_s8 = 0;
            arg0->unk_96.as_s16 = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
            func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
        }
    }
}
