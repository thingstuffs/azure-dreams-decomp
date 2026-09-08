#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8009C93C();
extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80175F44();
extern u16 D_80083462;




void func_80172D88(Rec_func_800A9E70_arg0 *arg0, s32 arg1, s32 arg2, void *arg3)
{
    if (arg0->unk_B5 == 0) {
        ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 &= 0x7F;
        if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 16) == 0)) {
            func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 16) == 0) {
                arg0->unk_8C = 0;
                arg0->unk_9A.as_s8 = 0x11;
                arg0->unk_9B.as_s8 = 0;
                arg0->unk_96.as_s16 = 0;
                ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
                arg0->unk_98 |= 8;
                func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
                ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
                ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
                return;
            }
        }
    } else {
        func_80175F44(arg0, arg1, arg2, 1, 1);
    }
}
