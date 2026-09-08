#include "common.h"

s32 rand();                                /* extern */

/* rand_sn: Return a random value modulo the given limit. */
s32 func_800C0E7C(s32 limit) {
    return rand() % limit;
}
