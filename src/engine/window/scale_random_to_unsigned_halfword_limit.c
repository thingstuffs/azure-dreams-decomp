#include "common.h"

#include "common.h"
#include "engine/window.h"
#include "sdk/libc.h"

/* Scale a random value by the low 16 bits of the limit. */
u32 scale_random_to_unsigned_halfword_limit(s32 limit) {
    return (u32) ((limit & 0xFFFF) * ((rand() * 2) & 0xFFFF)) >> 0x10;
}
