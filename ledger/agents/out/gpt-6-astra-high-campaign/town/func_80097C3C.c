#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


/* Adds each of the three motion increments to its corresponding position component. */
void func_8009539C(Rec_D_800E3D7C *motion) {
    motion->unk_00.at00_s32.v = (s32) (motion->unk_00.at00_s32.v + motion->unk_0C.as_s32);
    motion->unk_04.at00_s32.v = (s32) (motion->unk_04.at00_s32.v + motion->unk_10.at00_s32.v);
    motion->unk_08.at00_s32.v = (s32) (motion->unk_08.at00_s32.v + motion->unk_14.as_s32);
}
