#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"
#include "sdk/libgte.h"

extern void D_800AADB0();

   /* arg2 in initialize_person_vector */

typedef struct S_800AAE30_1 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
} S_800AAE30_1;   /* arg0 in initialize_person_vector */

/* Initialize a vector from the object's angle and assign its data pointer. */
void initialize_person_vector(S_800AAE30_1 *object, void *unusedContext, MotionDeltaView *outputVector) {
    outputVector->velocity_x = (s32) (rcos(object->unk_72) << 8);
    outputVector->velocity_y = (s32) ((0 - rsin(object->unk_72)) << 8);
    outputVector->velocity_z = 0;
    object->unk_50 = &D_800AADB0;
}
