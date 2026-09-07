#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"





extern s32 func_80047784();
extern s32 func_800A2B5C();
extern s32 func_800A4ACC();
extern s32 func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80174E3C;

void func_80174928(void *arg0, s32 arg1, void *arg2, void *arg3) {
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F;
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;
            (*(s32 * *)((u8 *)arg2 + 0x2C)) = &D_80174E3C;
            func_80047784(arg2,
                         *((((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7)
                           + (u8 *)&D_80174E3C),
                         0);
            func_800A4ACC(arg3);
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1;
        }
    }
}
