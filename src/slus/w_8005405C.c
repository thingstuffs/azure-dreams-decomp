#include "common.h"

typedef struct {
    u32 avail;   /* offset 0x0 */
    u32 locked;  /* offset 0x4 */
    u32 pad[1];  /* offset 0x8 - force %hi/%lo addressing (struct > 8 bytes) */
} S_800847D0;

extern S_800847D0 D_800847D0;

/* Tests bit (16+n) of D_800847D0.avail unless the corresponding bit (24+n)
   of D_800847D0.locked is set. */
s32 func_8005405C(s16 n) {
    S_800847D0 *p = &D_800847D0;
    if (p->locked & (0x1000000 << n))
        goto ret0;
    if (D_800847D0.avail & (0x10000 << n))
        return 1;
ret0:
    return 0;
}
