#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800AADB0;

   /* arg2 in initialize_person_vector */

typedef struct S_800AAE30_1 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
} S_800AAE30_1;   /* arg0 in initialize_person_vector */

/* Initialize a vector from the object's angle and assign its data pointer. */
void initialize_person_vector(S_800AAE30_1 *object, void *unusedContext, MotionDeltaView *outputVector) {
    outputVector->unk_0C = (s32) (func_80064584(object->unk_72) << 8);
    outputVector->unk_10 = (s32) ((0 - func_800644B8(object->unk_72)) << 8);
    outputVector->unk_14 = 0;
    object->unk_50 = &D_800AADB0;
}
