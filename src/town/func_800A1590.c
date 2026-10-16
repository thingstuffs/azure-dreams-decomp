#include "common.h"
#include "m2c_compat.h"

void townCallTheSameContextBothProcessingRoutines();            /* extern */
void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis();            /* extern */
void townResetObjectStatePassesSelectedResultCallee800A00E8(); /* extern */

typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;   /* arg0 in townRunBothUpdatesDecrementCountdownCheckCompletion */

/* Run both updates, decrement the countdown, and check for completion. */
void townRunBothUpdatesDecrementCountdownCheckCompletion(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx) {
    u16 countdown;

    townCallTheSameContextBothProcessingRoutines(update_ctx, update_data);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(update_ctx, update_data);
    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        townResetObjectStatePassesSelectedResultCallee800A00E8(state, update_ctx, update_data, finish_ctx);
    }
}
