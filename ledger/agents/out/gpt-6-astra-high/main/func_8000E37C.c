#include "common.h"

extern struct {
    s32 v;
    s32 pad[2];
} D_800287C8;

/* Clears the pending flag and returns 4 if it was set, otherwise 0. */
s32 func_8002137C(void) {
    s32 status;

    status = 0;
    if (D_800287C8.v != 0) {
        status = 4;
        D_800287C8.v = 0;
    }
    return status;
}
