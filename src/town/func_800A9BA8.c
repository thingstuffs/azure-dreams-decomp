#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082D58.h"

extern M2C_UNK D_800A7360;
extern s32 D_800D0DF8[];



/* Copy the indexed table value to the output and advance the object state. */
void func_800A7308(Rec_D_80082D58 *object, Rec_D_800E3D7C *output) {
    output->unk_14.as_s32 = D_800D0DF8[object->unk_90.as_s16];
    object->unk_50.as_pm = &D_800A7360;
}
