#include "common.h"
#include "sdk/libc.h"
#include "town/scene.h"


/* rand_sn: Return a random value modulo the given limit. */
s32 rand_sn(s32 limit) {
    return rand() % limit;
}
