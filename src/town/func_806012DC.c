#include "common.h"

extern s32 func_800168BC();

void func_806012DC(void) {
    s8 sp10[4];

    sp10[1] = 1;
    sp10[0] = 1;
    sp10[2] = 0;
    sp10[3] = 0;
    func_800168BC(sp10);
}

/* MECHANISM: One contiguous s8[4] frame object makes all four bytes observable
   through the callee pointer, preventing scalar-local dead-store deletion.
   Source write order yields three pre-call stores and the final store in the jal slot. */
