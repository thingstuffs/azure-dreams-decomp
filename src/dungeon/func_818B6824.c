#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern s16 func_800AD568(void *, s32);
extern M2C_UNK func_800B4C7C(s32, void *, s32, s32);


void func_818B6824(Rec_D_800E3D7C *arg0, s32 arg1) {
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 var_a1;

    if (func_8009D218(arg0, 1) == 0) {
        temp_v1 = func_800A6870(arg1 & 0xFF) + 8;
        var_a1 = temp_v1;
        if (arg0->unk_28 & 1) {
            var_a1 = temp_v1 << 1;
        }
        arg0->unk_64.as_u16 = (u16) (arg0->unk_64.as_u16 + var_a1);
        func_800AD568(arg0, var_a1);
        func_800B4C7C(0x8004, arg0, (s16) arg0->unk_64.as_u16, 1);
        func_800AD4D0(arg0);
    }
}
