#include "common.h"
#include "shared/types3a_types.h"

   /* arg0 in follow_linked_position_until_timeout */


typedef struct CopySource {
    u32 x;
    s32 y;
    s32 z;
} CopySource;

typedef struct CopyMiddle {
    s32 unk0[2];
    CopySource *source;
} CopyMiddle;

typedef struct CopyGlobal {
    s32 unk0[4];
    CopyMiddle *middle;
} CopyGlobal;


extern CopyGlobal D_800CFCB4;
extern void func_80094894(UnsignedCountdownView *, IntVector3 *, s32);

/* Copy source coordinates, decrement the counter, and call the handler when it becomes negative. */
void follow_linked_position_until_timeout(UnsignedCountdownView *state, IntVector3 *out, s32 handler_arg) {
    s16 remaining;

    out->x = D_800CFCB4.middle->source->x;
    out->y = D_800CFCB4.middle->source->y;
    out->z = D_800CFCB4.middle->source->z;
    remaining = state->unk_0A - 1;
    state->unk_0A = remaining;
    if (remaining < 0) {
        func_80094894(state, out, handler_arg);
    }
}
