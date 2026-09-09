#include "common.h"

typedef struct S_80093524_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80093524_0;   /* arg0 in func_80093524 */


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

typedef struct CopyOutput {
    s32 x;
    s32 y;
    s32 z;
} CopyOutput;


extern CopyGlobal D_800CFCB4;
extern void func_80094894(S_80093524_0 *, CopyOutput *, s32);

/* Copy source coordinates, decrement the counter, and call the handler when it becomes negative. */
void func_80093524(S_80093524_0 *state, CopyOutput *out, s32 handler_arg) {
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
