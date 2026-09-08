#include "common.h"

extern struct {
    s32 v;
    s32 pad[2];
} D_800287C8;

/* Clears a pending flag and returns 5 if it was set, or 0 otherwise. */
s32 func_800213A0(void) {
    s32 status;

    status = 0;
    if (D_800287C8.v != 0) {
        status = 5;
        D_800287C8.v = 0;
    }
    return status;
}
