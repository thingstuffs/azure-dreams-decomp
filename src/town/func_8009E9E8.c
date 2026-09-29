#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"

M2C_UNK func_8008F664();              /* extern */
extern M2C_UNK D_8009B8E8;
extern s32 D_800D0428[];


/* Initializes the target parameters and updates the owner's state. */
void func_8009C148(Rec_func_8009B828_arg0 *owner, Rec_D_800CFCB4 *target, EntityRec *parameters) {
    s32 combinedValue;

    target->unk_15 = 0;
    combinedValue = D_80083780.z.v + D_800D0428[0];
    parameters->unk_0C = 0;
    parameters->unk_10 = 0;
    parameters->flags14 = 0;
    parameters->z.v = combinedValue;
    func_8008F664(target, parameters);
    owner->unk_50 = &D_8009B8E8;
    owner->unk_6C.as_s16 = 4;
}
