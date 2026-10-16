#include "common.h"

typedef struct S_8004F95C {
    void (*func)(void);
    u8 pad4[0x28 - 0x4];
    s32 limit;
    s32 counter;
} S_8004F95C;

extern void reorderAndInterpolateSelectionMenuEntries(S_8004F95C *a0);
extern void func_8004F67C(void);

/* Updates state, advances its counter, and disables its callback when the prior count reaches the limit. */
void animateSelectionMenuIndexTransition(S_8004F95C *state) {
    reorderAndInterpolateSelectionMenuEntries(state);
    if (state->counter++ >= state->limit) {
        state->func = func_8004F67C;
    }
}
