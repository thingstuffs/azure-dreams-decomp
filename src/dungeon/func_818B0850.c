#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern s32 func_8009D218(void *arg0, s32 arg1);
extern s32 func_800A6870(s32 arg0);
extern void func_800AD4D0(void *arg0);
extern void func_800AD568(void *arg0, s32 arg1);
extern void func_800B4C7C(s32 arg0, void *arg1, s32 arg2, s32 arg3);


void func_818B0850(void *arg0, s32 arg1) {
    if (func_8009D218(arg0, 4) == 0) {
        register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s16 temp_v0;
        s32 var_a1;

        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        temp_v0 = ((Rec_D_800E3D7C *)arg0)->unk_28 & 4;
        var_a1 = temp_v1;
        if (temp_v0) {
            temp_v0 = (s32) (temp_v1 << 16) >> 18;
            var_a1 = temp_v1 + temp_v0;
        }
        ((Rec_D_800E3D7C *)arg0)->unk_64.as_u16 = (u16) (((Rec_D_800E3D7C *)arg0)->unk_64.as_u16 + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) ((Rec_D_800E3D7C *)arg0)->unk_64.as_u16, 1);
        func_800AD4D0(arg0);
    }
}
