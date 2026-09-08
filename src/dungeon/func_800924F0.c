#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"

/* Reset the entity to state 0x3A and clear its context's 0x20 flag. */
void func_80097C50(Rec_func_8008ACDC_arg0 *entity, M2C_UNK unused_1, M2C_UNK unused_2, Rec_D_800E3D7C *context) {
    entity->unk_9A.as_s8 = 0x3A;
    entity->unk_9B.as_s8 = 0;
    entity->unk_8C.as_s32 = 0;
    entity->unk_96.as_s16 = 0;
    context->unk_1C.as_s32 = (s32) (context->unk_1C.as_s32 & ~0x20);
}
