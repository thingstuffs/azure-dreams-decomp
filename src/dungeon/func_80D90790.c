#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"





extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80047784();
extern void func_8009C93C();
extern void func_80172050(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_8017386C[];

void func_80171F90(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(arg3) << 0x10) == 0) &&
        (func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300),
         ((func_800A2B5C(arg3) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;

        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0x17;
            ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x10;
            ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0x10;
            func_80172050();
        }

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0x11;
        ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
        ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017386C;
        func_80047784(arg2,
                      D_8017386C[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                      0);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;

        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 == 0x11) {
            func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
        }
    }
}
