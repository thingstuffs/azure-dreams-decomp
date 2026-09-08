#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8009B828_arg0.h"

M2C_UNK func_8008F664();              /* extern */
extern s32 D_80083788[];
extern M2C_UNK D_8009B8E8;
extern s32 D_800D0428[];




/* Initializes the target parameters and updates the owner's state. */
void func_8009C148(Rec_func_8009B828_arg0 *owner, Rec_D_800CFCB4 *target, Rec_D_800E3D7C *parameters) {
    s32 combinedValue;

    target->unk_15 = 0;
    combinedValue = D_80083788[0] + D_800D0428[0];
    parameters->unk_0C.as_s32 = 0;
    parameters->unk_10.at00_s32.v = 0;
    parameters->unk_14.as_s32 = 0;
    parameters->unk_08.at00_s32.v = combinedValue;
    func_8008F664(target, parameters);
    owner->unk_50 = &D_8009B8E8;
    owner->unk_6C.as_s16 = 4;
}
