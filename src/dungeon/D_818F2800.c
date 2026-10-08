#include "common.h"

extern void func_80024FA4(void);

/* Exact physical entry_pointer span; owner unresolved. */
const u32 D_80024000[1] __attribute__((aligned(4))) = {
    (u32)func_80024FA4
};
