#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"



extern u8 D_800DD878;
extern Rec_D_800E3D7C *D_800E3D7C;

void func_800A68F4(void) {
    if (D_800DD878 != 0) {
        D_800E3D7C->unk_1C.as_s32 = (s32) (D_800E3D7C->unk_1C.as_s32 | 0x10);
    }
}
