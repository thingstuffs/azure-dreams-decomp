#include "common.h"

typedef void (*Callback)(void *);

extern Callback D_800D4668[];

void func_800C1E50(void) {
    Callback *callback;

    callback = D_800D4668;
    if (*callback != 0) {
        do {
            (*callback)(callback);
            callback += 6;
        } while (*callback != 0);
    }
}

/* MECHANISM: The callback-array cursor stays live across indirect calls, selecting s0
   and the retail 0x18 frame; a do-while preserves the load/call/increment/reload CFG. */
