#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libgte.h"


typedef struct S_800B0654_0 {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x92];
    s32 unk_C0;
} S_800B0654_0;   /* arg2 in copy_adjusted_state_values */

   /* arg0 in copy_adjusted_state_values */

typedef struct S_800B0654_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800B0654_2;   /* arg1 in copy_adjusted_state_values */

/* Copy three source values into the destination state and store the adjusted calculation result. */
void copy_adjusted_state_values(MovingPosition *sourceValues, S_800B0654_2 *resultAdjustment, void *destinationState_arg) {
    S_800B0654_0 *destinationState = destinationState_arg;

    destinationState->unk_28 = (u16) sourceValues->x;
    destinationState->unk_2A = (u16) sourceValues->y;
    destinationState->unk_2C = (u16) sourceValues->z;
    destinationState->unk_C0 = (s32) (RotTransPers(destinationState_arg + 0x28, destinationState_arg + 0xB8,
        destinationState_arg + 0x90, destinationState_arg + 0x94) + resultAdjustment->unk_04);
}
