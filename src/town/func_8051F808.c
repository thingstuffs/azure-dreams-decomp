#include "common.h"

typedef s32 (*Callback)(s32);

extern s8 D_80016000[];

/* Run both callbacks and advance the object value when its status is zero. */
s32 func_80017008(void) {
    s8 *context_ref;
    void *object_state;

    context_ref = D_80016000;
    (*(Callback *)((s8 *)*(void **)((s8 *)*(void **)context_ref + 0x20) + 0x248))(1);
    (*(Callback *)((s8 *)*(void **)((s8 *)*(void **)context_ref + 0x20) + 0x244))(1);

    object_state = *(void **)((s8 *)*(void **)context_ref + 0x1C);
    if (*(s32 *)object_state != 0) {
        return 0;
    }
    *(s32 *)((s8 *)object_state + 8) += 0x20;
    return 1;
}
