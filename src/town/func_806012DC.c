#include "common.h"

extern s32 func_800168BC();

/* Pass the four-byte request 1, 1, 0, 0 to func_800168BC. */
void func_806012DC(void) {
    s8 request[4];

    request[1] = 1;
    request[0] = 1;
    request[2] = 0;
    request[3] = 0;
    func_800168BC(request);
}

/* MECHANISM: One contiguous s8[4] frame object makes all four bytes observable
   through the callee pointer, preventing scalar-local dead-store deletion.
   Source write order yields three pre-call stores and the final store in the jal slot. */
