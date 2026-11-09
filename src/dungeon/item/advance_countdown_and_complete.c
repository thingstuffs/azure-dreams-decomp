#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

typedef struct {
    u8 pad_0[8];
    s32 field_8;
    u8 pad_C[4];
    s16 field_10;
} S_80094274;

/* Advance the counter and set completion flags when the countdown expires. */
void advance_countdown_and_complete(S_80094274 *state)
{
    state->field_8++;
    if (--state->field_10 <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
