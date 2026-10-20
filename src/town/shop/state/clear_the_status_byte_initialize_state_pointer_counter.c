#include "common.h"
typedef struct MotionVector MotionVector;
typedef struct TownActor TownActor;
void move_toward_target_check_completion_countdown_expires(TownActor *actor, s32 context, MotionVector *motion, s32 extra);

typedef struct S_8009EB20_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009EB20_0;   /* arg1 in clear_the_status_byte_initialize_state_pointer_counter */

typedef struct S_8009EB20_1 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009EB20_1;   /* arg0 in clear_the_status_byte_initialize_state_pointer_counter */

/* Clear the status byte and initialize the state pointer and counter. */
void clear_the_status_byte_initialize_state_pointer_counter(S_8009EB20_1 *state, S_8009EB20_0 *status) {
    status->unk_15 = 0;
    state->unk_50 = &move_toward_target_check_completion_countdown_expires;
    state->unk_6C = 8;
}
