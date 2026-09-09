#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"




M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174038[];

void func_8017208C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0) && (func_800C7930(arg3 - 0x20, arg1, 8, 0x300), ((func_800A2B5C(arg3) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;
        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0x17;
            if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x1000) {
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 | 0x4000);
            } else {
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0xBFFF);
            }
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_AC = (u8) ((Rec_D_800E3D7C *)arg3)->unk_00.at03_u8.v;
            ((Rec_D_800E3D7C *)arg3)->unk_00.at03_u8.v = 0xFFU;
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7E;
        } else {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0x11;
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
        }
        ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 8;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_80174038;
        func_80047784(arg2, D_80174038[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
        func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
        if (!(((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0x8000)) {
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0xFEFFFFFF);
        }
    }
}

/* MECHANISM: Retail's 0x80172154/0x80172180 targets are local CFG joins, not callees.
   A u8 path result carries 0x7E/0x7C into the shared arg3+0x84 store.
   The held argument roles naturally produce the 0x30 frame and s1/s0/s3/s2 saves. */
