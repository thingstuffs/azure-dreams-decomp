#include "common.h"

extern void *D_800FE490[];

void func_8008FD20(void *arg0) {
    *(void **)arg0 = D_800FE490[0];
    *((void **)arg0 + 1) = D_800FE490;
    *((void **)D_800FE490[0] + 1) = arg0;
    D_800FE490[0] = arg0;
}

/* MECHANISM: Frameless leaf with the global array address reused directly.
   Statement order preserves the load/store/reload chain and return-slot store.
   The town-home 2.7.2-cdk-G0 lineage closes the inherited +1 length drift. */
