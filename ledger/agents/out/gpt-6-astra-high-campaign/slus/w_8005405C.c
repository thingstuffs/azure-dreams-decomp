#include "common.h"

typedef struct {
    u32 avail;   /* offset 0x0 */
    u32 locked;  /* offset 0x4 */
    u32 pad[1];  /* offset 0x8 - force %hi/%lo addressing (struct > 8 bytes) */
} S_800847D0;

extern S_800847D0 D_800847D0;

/* Returns whether the indexed availability bit is set and its lock bit is clear. */
s32 func_8005405C(s16 bit_index) {
    S_800847D0 *flags = &D_800847D0;
    if (flags->locked & (0x1000000 << bit_index))
        goto ret0;
    if (D_800847D0.avail & (0x10000 << bit_index))
        return 1;
ret0:
    return 0;
}
