#include "common.h"

extern void func_8002401C(u8 *, u8 *, void *);

/* Exact physical entry_pointer span; owner unresolved. */
const u32 D_80024000[1] __attribute__((aligned(4))) = {
    (u32)func_8002401C
};
