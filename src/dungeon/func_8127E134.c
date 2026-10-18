/* Relink of matched dungeon/is_global_effect_enabled at file 0x1274134; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/sys_flags.h"


/* Returns whether bit 0x10 is set in D_80013714[0]. */
s32 is_bit_10_is_set(void) {
    if (D_80013714 & 0x10) {
        return 1;
    }
    return 0;
}
