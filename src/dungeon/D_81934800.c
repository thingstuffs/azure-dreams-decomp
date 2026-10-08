#include "common.h"

extern void func_80024128(void *, void *);

/* Bank entry pointer. Storage owner remains unresolved. */
const u32 D_80024000[1] __attribute__((aligned(4))) = {
    (u32)func_80024128,
};
