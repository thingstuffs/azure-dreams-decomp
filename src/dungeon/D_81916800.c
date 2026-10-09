#include "common.h"

extern void func_80025408(void *, void *, void *);

/* Bank entry pointer (selector-44 image loaded at 0x80024000). Storage owner remains unresolved. */
const u32 D_80024000[1] __attribute__((aligned(4))) = {
    (u32)func_80025408,
};
