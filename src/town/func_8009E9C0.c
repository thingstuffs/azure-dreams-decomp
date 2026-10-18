#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
void update_motion_toward_shared_target(Rec_func_8009B828_arg0 *state, s32 context, EntityRec *motion, s32 transition_arg);

typedef struct S_8009C120_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009C120_0;   /* arg1 in initialize_target_motion_state */

typedef struct S_8009C120_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C120_1;   /* arg2 in initialize_target_motion_state */

typedef struct S_8009C120_2 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009C120_2;   /* arg0 in initialize_target_motion_state */

/* Clear status and values, then initialize the state's data pointer and mode. */
void initialize_target_motion_state(S_8009C120_2 *state, S_8009C120_0 *status, S_8009C120_1 *values) {
    status->unk_15 = 0;
    values->unk_0C = 0;
    values->unk_10 = 0;
    values->unk_14 = 0;
    state->unk_50 = &update_motion_toward_shared_target;
    state->unk_6C = 7;
}
