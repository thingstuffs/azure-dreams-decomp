#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"



extern s8 D_800DD878;
extern Rec_D_800E3D7C *D_800E3D7C;

void func_800A68C0(void) {
    D_800DD878 = ((u32) D_800E3D7C->unk_1C.as_u32 >> 4) & 1;
    D_800E3D7C->unk_1C.as_u32 = (u32) (D_800E3D7C->unk_1C.as_u32 & ~0x10);
}
