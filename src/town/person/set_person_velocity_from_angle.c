#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"
#include "sdk/libgte.h"
#include "town/person.h"

extern void apply_town_motion_step();

   /* arg2 in set_person_velocity_from_angle */

typedef struct S_800AAE30_1 {
    u8 pad_00[0x50];
    void (*unk_50)();
    u8 pad_54[0x1E];
    s16 unk_72;
} S_800AAE30_1;   /* arg0 in set_person_velocity_from_angle */

/* Initialize a vector from the object's angle and assign its data pointer. */
void set_person_velocity_from_angle(S_800AAE30_1 *object, void *unusedContext, MotionDeltaView *outputVector) {
    outputVector->velocity_x = (s32) (rcos(object->unk_72) << 8);
    outputVector->velocity_y = (s32) ((0 - rsin(object->unk_72)) << 8);
    outputVector->velocity_z = 0;
    object->unk_50 = &apply_town_motion_step;
}
